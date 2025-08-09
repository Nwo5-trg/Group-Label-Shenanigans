#include "Include.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

void GroupLabels::updateLabelForTrigger(EffectGameObject* trigger) {
    int id = trigger->m_objectID;
    if (Utils::triggerBlacklist.contains(id)) return;
    if (Settings::triggerWhitelist.contains(id)) return;

    if (trigger->getOpacity() == 0) return;
    if (!trigger->isVisible()) return;

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

    CCSize objScale = {trigger->m_scaleX, trigger->m_scaleY};
    float rotation = trigger->getRotation();

    // create label

    auto label = getLabelNode(trigger);
    if (labelInfoUpdated) {
        getLabelFromInfo();
        label->setString(Cache::labelCharBuffer);
    }
    label->setPosition(Utils::getOffsetPos(trigger, false));
    label->setOpacity(Cache::layerAlpha);
    
    label->setScaleX(objScale.width * Settings::scale);
    label->setScaleY(objScale.height * Settings::scale);

    float widthLimit = Settings::widthLimit * std::max(objScale.width, objScale.height);
    if (widthLimit < 50.0f) {
        float width = label->getScaledContentWidth();
        if (width > widthLimit) {
            label->setScale(label->getScale() * (widthLimit / width));
        }
    }

    if (Settings::rotate) label->setRotation(rotation);

    if (labelInfoUpdated) Cache::labelInfoMap[trigger] = Cache::labelInfo;

    // create extra
    if (!Settings::extras) return;
    if (!Utils::extrasMap.contains(id)) return;

    auto extra = getExtrasNode(trigger);
    extra->setPosition(Utils::getOffsetPos(trigger, true));
    updateExtrasColor(extra, trigger);
    
    extra->setScaleX(objScale.width * Settings::extrasScale);
    extra->setScaleY(objScale.height * Settings::extrasScale);

    extra->setRotation(rotation);
}