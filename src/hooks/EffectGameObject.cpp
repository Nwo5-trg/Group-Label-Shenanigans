#include <Geode/modify/EffectGameObject.hpp>
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(EffectGameObject) {
    void setObjectLabel(CCLabelBMFont* p0) {
        EffectGameObject::setObjectLabel(p0);
        if (!Utils::triggerWhitelist.contains(m_objectID)) {
            p0->setVisible(false);
        }
    }
};