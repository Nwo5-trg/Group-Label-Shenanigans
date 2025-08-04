#include "Include.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;
using namespace GroupLabels;

void GroupLabels::update(LevelEditorLayer* editor) {
    Cache::View::size = CCDirector::get()->getWinSize();
    Cache::View::zoom = editor->m_objectLayer->getScale();
    Cache::View::relativeCenter = (
        (Cache::View::size / 2) - 
        ccp( // objects are offset soo
            editor->m_objectLayer->getPositionX(), 
            editor->m_objectLayer->getPositionY() 
            - editor->m_editorUI->m_toolbarHeight / 2
        )
    ) / Cache::View::zoom;
    Cache::View::cullDistance = Cache::View::size.width / Cache::View::zoom;
    Cache::View::cullDistance = (Cache::View::cullDistance * Cache::View::cullDistance) * Constants::cullDistanceBuffer;

    Cache::updatedTriggers.clear();

    Cache::currentLayer = editor->m_currentLayer;

    for (auto trigger : Cache::triggers) {
        updateLabelForTrigger(trigger);
    }

    for (auto it = Cache::labelMap.begin(); it != Cache::labelMap.end();) {
        auto* trigger = it->first;
        if (!Cache::updatedTriggers.contains(trigger)) {
            it->second->removeMeAndCleanup();
            it = Cache::labelMap.erase(it);
            Cache::labelInfoMap.erase(trigger);
        } else it++;
    }
}