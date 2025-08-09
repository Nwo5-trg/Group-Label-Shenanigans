#include "Include.hpp"
#include "../shared/Cache.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

CCLabelBMFont* GroupLabels::getLabelNode(EffectGameObject* trigger) {
    if (Cache::labelMap.contains(trigger)) return Cache::labelMap[trigger];
    auto label = CCLabelBMFont::create("", "bigFont.fnt");
    label->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
    Cache::textObjectLayer->addChild(label);
    Cache::labelMap[trigger] = label;
    return label;
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

CCLabelBMFont* GroupLabels::getExtrasNode(EffectGameObject* trigger) {
    if (Cache::extrasMap.contains(trigger)) return Cache::extrasMap[trigger];
    auto label = CCLabelBMFont::create(".", "bigFont.fnt");
    label->setZOrder(-1);
    Cache::textObjectLayer->addChild(label);
    Cache::extrasMap[trigger] = label;
    return label;
}

void GroupLabels::updateExtrasColor(CCLabelBMFont* extra, EffectGameObject* trigger) {
    auto type = Utils::extrasMap[trigger->m_objectID];
    bool activated = false;
    switch (type) {
        case ExtrasType::Activate: {
            activated = trigger->m_activateGroup; break;
        }
        case ExtrasType::TouchToggle: {
            activated = trigger->m_touchToggleMode == TouchTriggerType::ToggleOn; break;
        }
        case ExtrasType::ControlID: {
            activated = trigger->m_targetControlID; break;
        }
        case ExtrasType::Blending: {
            activated = trigger->m_usesBlending; break;
        }
        case ExtrasType::PulseTargetType: {
            activated = trigger->m_pulseTargetType == 1; break;
        }
        case ExtrasType::Override: {
            activated = static_cast<CountTriggerGameObject*>(trigger)->m_isOverride; break;
        }
        case ExtrasType::Follow: {
            activated = static_cast<CameraTriggerGameObject*>(trigger)->m_followObject; break;
        }
    }
    auto& pair = activated ? Utils::extrasColorMap[type].second : Utils::extrasColorMap[type].first;
    extra->setColor(pair.first);
    extra->setOpacity(Cache::layerAlpha * pair.second);
}