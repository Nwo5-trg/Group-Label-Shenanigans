#include "Include.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

void GroupLabels::updateLabelForTrigger(EffectGameObject* trigger) {
    int id = trigger->m_objectID;
    if (Utils::triggerBlacklist.contains(id)) return;
    if (Settings::triggerWhitelist.contains(id)) return;

    auto pos = trigger->getPosition();
    if ( // culling
        !trigger->m_isSelected 
        && ccpDistanceSQ(Cache::View::relativeCenter, pos) 
        > Cache::View::cullDistance
    ) return;

    getLabelInfoForTrigger(trigger);
    if (Settings::hide0Group && Cache::labelInfo == 0) return;
    bool labelInfoUpdated = Cache::labelInfoMap[trigger] != Cache::labelInfo;

    Utils::updateLayerAlpha(trigger);

    Cache::updatedTriggers.insert(trigger);

    auto label = getLabelNode(trigger);
    if (labelInfoUpdated) {
        getLabelFromInfo();
        label->setString(Cache::labelCharBuffer);
    }
    label->setPosition(Utils::getTriggerBodyPos(trigger));
    label->setOpacity(Cache::layerAlpha);
    
    CCSize objScale = {trigger->m_scaleX, trigger->m_scaleY};
    label->setScaleX(objScale.width * Settings::scale);
    label->setScaleY(objScale.height * Settings::scale);

    float widthLimit = Settings::widthLimit * std::max(objScale.height, objScale.width);
    if (widthLimit < 50.0f) {
        float width = label->getScaledContentWidth();
        if (width > widthLimit) {
            label->setScale(label->getScale() * (widthLimit / width));
        }
    }

    if (Settings::rotate) label->setRotation(trigger->getRotation());

    if (labelInfoUpdated) Cache::labelInfoMap[trigger] = Cache::labelInfo;
}

void GroupLabels::getLabelInfoForTrigger(EffectGameObject* trigger) {
    int id = trigger->m_objectID;

    auto type = LabelType::Target;
    if (Utils::labelTypeMap.contains(id)) type = Utils::labelTypeMap[id];

    Cache::labelInfo.reset(type);

    switch (type) {
        case LabelType::Target: {
            Cache::labelInfo.target = trigger->m_targetGroupID;
            break;
        }
        case LabelType::Center: {
            Cache::labelInfo.target = trigger->m_centerGroupID;
            break;
        }
        case LabelType::Target_Center: {
            Cache::labelInfo.target = trigger->m_targetGroupID;
            Cache::labelInfo.center = trigger->m_centerGroupID;
            break;
        }
        case LabelType::TargetCenter: {
            Cache::labelInfo.target = trigger->m_targetGroupID;
            Cache::labelInfo.ext = trigger->m_centerGroupID;
            break;
        }
        case LabelType::Item: {
            Cache::labelInfo.target = trigger->m_itemID;
            break;
        }
        case LabelType::Target_Anim: {
            Cache::labelInfo.target = trigger->m_targetGroupID;
            Cache::labelInfo.center = trigger->m_animationID;
            break;
        }
        case LabelType::Anim_TargetCenter: {
            Cache::labelInfo.target = trigger->m_animationID;
            Cache::labelInfo.center = trigger->m_targetGroupID;
            Cache::labelInfo.ext2 = trigger->m_centerGroupID;
            break;
        }
        case LabelType::TargetCenter_ItemItem2: {
            Cache::labelInfo.target = trigger->m_targetGroupID;
            Cache::labelInfo.ext = trigger->m_centerGroupID;
            Cache::labelInfo.center = trigger->m_itemID;
            Cache::labelInfo.ext2 = trigger->m_itemID2;
            break;
        }
        case LabelType::Target_ItemItem2: {
            Cache::labelInfo.target = trigger->m_targetGroupID;
            Cache::labelInfo.center = trigger->m_itemID;
            Cache::labelInfo.ext2 = trigger->m_itemID2;
            break;
        }
        case LabelType::Item_Target: {
            Cache::labelInfo.target = trigger->m_itemID;
            Cache::labelInfo.center = trigger->m_targetGroupID;
            break;
        }
        case LabelType::Target_Item: {
            Cache::labelInfo.target = trigger->m_targetGroupID;
            Cache::labelInfo.center = trigger->m_itemID;
            break;
        }
        case LabelType::Gradient: {
            Cache::labelInfo.target = static_cast<GradientTriggerObject*>(trigger)->m_gradientID;
            break;
        }
        case LabelType::EnterEffect: {
            Cache::labelInfo.target = static_cast<EnterEffectObject*>(trigger)->m_enterChannel;
            break;
        }
        case LabelType::SFX: {
            Cache::labelInfo.target = static_cast<SFXTriggerGameObject*>(trigger)->m_soundID;
            break;
        }
        case LabelType::Color: {
            Cache::labelInfo.target = trigger->m_targetColor;
            break;
        }
        case LabelType::PulseColor: {
            Cache::labelInfo.target = trigger->m_targetGroupID;
            break;
        }
    }
}

// idc vro im not "refactoring" this is clean enough
void GroupLabels::getLabelFromInfo() {
    char* ptr = Cache::labelCharBuffer;
    switch (Cache::labelInfo.type) {
        case LabelType::Target: TO_CHARS(ptr, Cache::labelInfo.target); break;
        case LabelType::Center: TO_CHARS(ptr, Cache::labelInfo.target); break;
        case LabelType::Target_Center: {
            TO_CHARS(ptr, Cache::labelInfo.target); ADD_CHAR(ptr, '\n');
            TO_CHARS(ptr, Cache::labelInfo.center); break;
        }
        case LabelType::TargetCenter: {
            TO_CHARS(ptr, Cache::labelInfo.target); ADD_CHAR(ptr, '/');
            TO_CHARS(ptr, Cache::labelInfo.ext); break;
        }
        case LabelType::Item: TO_CHARS(ptr, Cache::labelInfo.target); break;
        case LabelType::Target_Anim: {
            TO_CHARS(ptr, Cache::labelInfo.target); ADD_CHAR(ptr, '\n');
            TO_CHARS(ptr, Cache::labelInfo.center); break;
        }
        case LabelType::Anim_TargetCenter: {
            TO_CHARS(ptr, Cache::labelInfo.target); ADD_CHAR(ptr, '\n');
            TO_CHARS(ptr, Cache::labelInfo.center); ADD_CHAR(ptr, '/');
            TO_CHARS(ptr, Cache::labelInfo.ext2); break;
        }
        case LabelType::TargetCenter_ItemItem2: {
            TO_CHARS(ptr, Cache::labelInfo.target); ADD_CHAR(ptr, '/');
            TO_CHARS(ptr, Cache::labelInfo.ext); ADD_CHAR(ptr, '\n');
            TO_CHARS(ptr, Cache::labelInfo.center); ADD_CHAR(ptr, '/');
            TO_CHARS(ptr, Cache::labelInfo.ext2); break;
        }
        case LabelType::Target_ItemItem2: {
            TO_CHARS(ptr, Cache::labelInfo.target); ADD_CHAR(ptr, '\n');
            TO_CHARS(ptr, Cache::labelInfo.center); ADD_CHAR(ptr, '/');
            TO_CHARS(ptr, Cache::labelInfo.ext2); break;
        }
        case LabelType::Item_Target: {
            TO_CHARS(ptr, Cache::labelInfo.target); ADD_CHAR(ptr, '\n');
            TO_CHARS(ptr, Cache::labelInfo.center); break;
        }
        case LabelType::Target_Item: {
            TO_CHARS(ptr, Cache::labelInfo.target); ADD_CHAR(ptr, '\n');
            TO_CHARS(ptr, Cache::labelInfo.center); break;
        }
        case LabelType::Gradient: TO_CHARS(ptr, Cache::labelInfo.target); break;
        case LabelType::EnterEffect: TO_CHARS(ptr, Cache::labelInfo.target); break;
        case LabelType::SFX: TO_CHARS(ptr, Cache::labelInfo.target); break;
        case LabelType::Color: TO_CHARS_COL(ptr, Cache::labelInfo.target); break;
        case LabelType::PulseColor: TO_CHARS_COL(ptr, Cache::labelInfo.target); break;
    }
    ADD_CHAR(ptr, '\0');
}

CCLabelBMFont* GroupLabels::getLabelNode(EffectGameObject* trigger) {
    if (Cache::labelMap.contains(trigger)) return Cache::labelMap[trigger];
    auto label = CCLabelBMFont::create("", "bigFont.fnt");
    label->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    Cache::textObjectLayer->addChild(label);
    Cache::labelMap[trigger] = label;
    return label;
}