#include <Geode/modify/LevelEditorLayer.hpp>
#include "../group-labels/Update.hpp"
#include "../shared/Cache.hpp"

using namespace geode::prelude;

class $modify(LevelEditorLayer) {
    bool init(GJGameLevel* p0, bool p1) {	
		if (!LevelEditorLayer::init(p0, p1)) return false;

        Cache::labelMap.clear();
        Cache::groupMap.clear();

        Cache::textObjectLayer = CCLayer::create();
        Cache::textObjectLayer->setPosition(0.0f, 0.0f);
        Cache::textObjectLayer->setZOrder(5000);
        Cache::textObjectLayer->setID("group-labels-node"_spr);
        m_objectLayer->addChild(Cache::textObjectLayer);

        updateTriggers();
        
        return true;
    }

    void updateDebugDraw() {
        LevelEditorLayer::updateDebugDraw();
        // ik with mods like quickfill its technically possible to not
        // update this properly but ehhhh fuck off idc enough to come up with something better
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
            if (obj->m_isTrigger) Cache::triggers.push_back(static_cast<EffectGameObject*>(obj));
        }
    }
};