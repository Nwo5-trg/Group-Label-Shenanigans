#include "Utils.hpp"
#include "../shared/Settings.hpp"

using namespace geode::prelude;

CCPoint Utils::rotatePoint(CCPoint pos, CCPoint pivot, float rad) {
    if (rad == 0.0f) return pos;
    auto r = pos - pivot;
	float cos = cosf(rad); float sin = sinf(rad);
	float t = r.x;
	r.x = t * cos - r.y * sin + pivot.x;
	r.y = t * sin + r.y * cos + pivot.y;
	return r;
}

std::unordered_set<int> Utils::parseIntArray(const std::string& input) {
    std::unordered_set<int> intSet;
    auto start = 0;
    while (true) {
        auto comma = input.find(',', start);
        auto num = std::strtol(input.substr(start, comma - start).c_str(), nullptr, 10);
        if (num != 0) intSet.insert(num);
        if (comma == std::string::npos) break;
        start = comma + 1;
    }
    return intSet;
}

CCPoint Utils::getTriggerBodyPos(GameObject* obj) {
    auto objPos = obj->getPosition();
    auto bodyPos = ccp(objPos.x + Settings::xOff * obj->m_scaleX, objPos.y + Settings::yOff * obj->m_scaleY);
    return rotatePoint(bodyPos, objPos, -obj->getRotation() * Constants::degToRad);
}

int Utils::getTriggerGroup(EffectGameObject* trigger) {
    int id = trigger->m_objectID;
    auto type = LabelType::TargetGroup;
    if (labelTypeMap.contains(id)) type = labelTypeMap[id];

    switch (type) {
        case LabelType::TargetGroup: return trigger->m_targetGroupID;
        case LabelType::CenterGroup: return trigger->m_centerGroupID;
        case LabelType::ItemID: return trigger->m_itemID;
        case LabelType::EnterEffect: return static_cast<EnterEffectObject*>(trigger)->m_enterChannel;
        case LabelType::SFXID: return static_cast<SFXTriggerGameObject*>(trigger)->m_soundID;
        case LabelType::ColorChannel: return trigger->m_targetColor;
        case LabelType::AnimationID: return trigger->m_animationID;
        case LabelType::GradientID: return static_cast<GradientTriggerObject*>(trigger)->m_gradientID;
    }
}