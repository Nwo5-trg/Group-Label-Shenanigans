#include <Geode/modify/LevelEditorLayer.hpp>
#include "../group-labels/Include.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"

using namespace geode::prelude;

class $modify(LevelEditorLayer) {
    bool init(GJGameLevel* p0, bool p1) {	
		if (!LevelEditorLayer::init(p0, p1)) return false;

        updateTriggers();
        Settings::updateSettings();
        
        return true;
    }
    
    void updateDebugDraw() {
        LevelEditorLayer::updateDebugDraw();
        // ik with mods like quickfill its technically possible to noy update this properly 
        // but ehhhh fuck off idc enough to come up with something better
        int objects = m_objects->count();
        if (objects != Cache::lastObjectCount) {
            updateTriggers();
        }
        Cache::lastObjectCount = objects;

        GroupLabels::update(this);
    }

    void updateTriggers() {
        Cache::triggers.clear();
        for (auto obj : CCArrayExt<GameObject*>(m_objects)) {
            if (obj->m_isTrigger) {
                auto trigger = static_cast<EffectGameObject*>(obj);
                hideObjectLabel(trigger);
                Cache::triggers.push_back(trigger);
            }
        }
    }
    
    void hideObjectLabel(EffectGameObject* trigger) {
        auto label = trigger->m_objectLabel;
        if (label && !Settings::triggerWhitelist.contains(trigger->m_objectID)) {
            label->setVisible(false);
        }
    }
};