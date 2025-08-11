#include <Geode/modify/EffectGameObject.hpp>
#include "../shared/Settings.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(EffectGameObject) {
    void customSetup() {
        EffectGameObject::customSetup();

        if (
            LevelEditorLayer::get() &&
            !Utils::triggerBlacklist.contains(m_objectID) &&
            !Settings::triggerWhitelist.contains(m_objectID)
        ) m_hasSpecialChild = true;
    }
};