#include "Update.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

void GroupLabels::update(LevelEditorLayer* editor) {
    auto size = CCDirector::get()->getWinSize();
    float zoom = editor->m_objectLayer->getScale();
    auto relativeCenter = (
        (size / 2) - 
        ccp( // objects are offset soo
            editor->m_objectLayer->getPositionX(), 
            editor->m_objectLayer->getPositionY() 
            - editor->m_editorUI->m_toolbarHeight / 2
        )
    ) / zoom;
    float cullDistance = size.width / zoom; 
    cullDistance = (cullDistance * cullDistance) * Constants::cullDistanceBuffer;

    Cache::updatedTriggers.clear();

    // in my search for the fastest way to convert shit to a string we are going c style :3
    // (this is an awful idea and a direct result of my laziness)
    char c[12];

    for (auto trigger : Cache::triggers) {
        int id = trigger->m_objectID;
        if (Utils::triggerBlacklist.contains(id)) continue;
        if (Utils::triggerWhitelist.contains(id)) continue;

        auto pos = trigger->getPosition();
        if ( // culling
            !trigger->m_isSelected 
            && ccpDistanceSQ(relativeCenter, pos) 
            > cullDistance
        ) continue;

        int group = Utils::getTriggerGroup(trigger);
        if (Settings::hide0Group && group == 0) continue;

        auto res = std::to_chars(c, c + 12, group);
        if (res.ec != std::errc()) continue;
        *res.ptr = '\0';

        Cache::updatedTriggers.insert(trigger);

        auto label = getLabel(trigger);
        if (Cache::groupMap[trigger] != group) label->setString(c);
        label->setPosition(Utils::getTriggerBodyPos(trigger));
        label->setScaleX(trigger->m_scaleX * Settings::scale);
        label->setScaleY(trigger->m_scaleY * Settings::scale);
        if (Settings::rotate) label->setRotation(trigger->getRotation());

        Cache::groupMap[trigger] = group;
    }

    for (auto it = Cache::labelMap.begin(); it != Cache::labelMap.end();) {
        auto* trigger = it->first;
        if (!Cache::updatedTriggers.contains(trigger)) {
            it->second->removeMeAndCleanup();
            it = Cache::labelMap.erase(it);
            Cache::groupMap.erase(trigger);
        } else it++;
    }
}

void GroupLabels::updateLayerAlpha(GameObject* obj) {
    Cache::layerAlphaMultiplier = Cache::currentLayer == -1 ||
        ((obj->m_editorLayer == Cache::currentLayer)
        || (obj->m_editorLayer2 == Cache::currentLayer))
    ? 1.0f : Settings::layerAlphaMultiplier;
}

CCLabelBMFont* GroupLabels::getLabel(EffectGameObject* trigger) {
    if (Cache::labelMap.contains(trigger)) return Cache::labelMap[trigger];
    auto label = CCLabelBMFont::create("0", "bigFont.fnt");
    Cache::textObjectLayer->addChild(label);
    Cache::labelMap[trigger] = label;
    return label;
}