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

    Cache::updatedTriggers.insert(trigger);

    float rotation = trigger->getRotation();

    // create label

    auto label = getLabelNode(trigger);
    if (labelInfoUpdated) {
        getLabelFromInfo();
        label->setString(Cache::labelCharBuffer);
    }
    label->setPosition(Utils::getOffsetPos(trigger, false));
    label->setScale(Settings::scale);

    if (Settings::widthLimit < 50.0f) {
        float width = label->getScaledContentWidth();
        if (width > Settings::widthLimit) {
            label->setScale(label->getScale() * (Settings::widthLimit / width));
        }
    }

    if (!Settings::rotate) label->setRotation(-rotation);

    if (labelInfoUpdated) Cache::labelInfoMap[trigger] = Cache::labelInfo;

    // create extra

    if (!Settings::extras) return;
    if (!Utils::extrasMap.contains(id)) return;

    auto extra = getExtrasNode(trigger);
    extra->setPosition(Utils::getOffsetPos(trigger, true));
    extra->setScale(Settings::extrasScale);
    updateExtrasColor(extra, trigger);
}