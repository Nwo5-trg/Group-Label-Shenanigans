#include "Utils.hpp"
#include "../shared/Settings.hpp"
#include "../shared/Cache.hpp"

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

char* Utils::to_chars_col(char* first, char* last, int value) {
    if (colorConversionsMap.contains(value)) {
        auto str = colorConversionsMap[value];
        return std::copy(str, str + std::strlen(str), first);
    }
    return std::to_chars(first, last, value).ptr;
}

CCPoint Utils::getTriggerBodyPos(GameObject* obj) {
    auto objPos = obj->getPosition();
    auto bodyPos = ccp(
        objPos.x + Settings::xOff * obj->m_scaleX, 
        objPos.y + (Utils::centeredTriggersList.contains(obj->m_objectID) 
            ? 0.0f : Settings::yOff) * obj->m_scaleY
    );
    return rotatePoint(bodyPos, objPos, -obj->getRotation() * Constants::degToRad);
}

void Utils::updateLayerAlpha(GameObject* obj) {
    Cache::layerAlpha = Cache::currentLayer == -1 ||
        ((obj->m_editorLayer == Cache::currentLayer)
        || (obj->m_editorLayer2 != 0 
            && obj->m_editorLayer2 == Cache::currentLayer))
    ? 255 : 255 * Settings::layerAlphaMultiplier;
}

void Utils::updateLabelTypeMap() {
    switch (Settings::moreLabelInfo) {
        case MapType::MoreLabelInfo: {
            labelTypeMap = {
                {1914, LabelType::Center}, {2914, LabelType::Center},

                {3640, LabelType::Target_Center},

                {1346, LabelType::TargetCenter}, {2067, LabelType::TargetCenter}, {3016, LabelType::TargetCenter},
                {3006, LabelType::TargetCenter}, {3007, LabelType::TargetCenter}, {3008, LabelType::TargetCenter},
                {3009, LabelType::TargetCenter}, {3010, LabelType::TargetCenter}, {3608, LabelType::TargetCenter},
                {3613, LabelType::TargetCenter}, {1912, LabelType::TargetCenter},

                {1817, LabelType::Item}, {3641, LabelType::Item}, {3617, LabelType::Item}, 
                {1816, LabelType::Item},
                
                {1585, LabelType::Target_Anim},

                {3033, LabelType::Anim_TargetCenter},
                
                {3620, LabelType::TargetCenter_ItemItem2}, {3609, LabelType::TargetCenter_ItemItem2},

                {3619, LabelType::Target_ItemItem2}, {1815, LabelType::Target_ItemItem2},

                {3614, LabelType::Item_Target},

                {1611, LabelType::Target_Item}, {1811, LabelType::Target_Item}, {3615, LabelType::Target_Item},

                {2903, LabelType::Gradient},

                {22, LabelType::EnterEffect}, {24, LabelType::EnterEffect}, {23, LabelType::EnterEffect},
                {25, LabelType::EnterEffect}, {26, LabelType::EnterEffect}, {27, LabelType::EnterEffect},
                {28, LabelType::EnterEffect}, {55, LabelType::EnterEffect}, {56, LabelType::EnterEffect},
                {57, LabelType::EnterEffect}, {58, LabelType::EnterEffect}, {59, LabelType::EnterEffect},
                {1915, LabelType::EnterEffect}, {3017, LabelType::EnterEffect}, {3019, LabelType::EnterEffect},
                {3018, LabelType::EnterEffect}, {3020, LabelType::EnterEffect}, {3021, LabelType::EnterEffect},
                {3023, LabelType::EnterEffect},

                {1934, LabelType::SFX}, {3602, LabelType::SFX},

                {899, LabelType::Color},

                {1006, LabelType::PulseColor}
            };
        }
        case MapType::Vanilla: {
            labelTypeMap = {
                {1346, LabelType::TargetCenter}, {2067, LabelType::TargetCenter}, {3016, LabelType::TargetCenter},
                {3006, LabelType::TargetCenter}, {3007, LabelType::TargetCenter}, {3008, LabelType::TargetCenter},
                {3009, LabelType::TargetCenter}, {3010, LabelType::TargetCenter}, {3608, LabelType::TargetCenter},
                {3613, LabelType::TargetCenter}, {1912, LabelType::TargetCenter}, 

                {1817, LabelType::Item}, {3641, LabelType::Item}, {3614, LabelType::Item},
                {3615, LabelType::Item}, {3617, LabelType::Item}, {1816, LabelType::Item},

                {1914, LabelType::Center},

                {22, LabelType::EnterEffect}, {24, LabelType::EnterEffect}, {23, LabelType::EnterEffect},
                {25, LabelType::EnterEffect}, {26, LabelType::EnterEffect}, {27, LabelType::EnterEffect},
                {28, LabelType::EnterEffect}, {55, LabelType::EnterEffect}, {56, LabelType::EnterEffect},
                {57, LabelType::EnterEffect}, {58, LabelType::EnterEffect}, {59, LabelType::EnterEffect},
                {1915, LabelType::EnterEffect}, {3017, LabelType::EnterEffect}, {3019, LabelType::EnterEffect},
                {3018, LabelType::EnterEffect}, {3020, LabelType::EnterEffect}, {3021, LabelType::EnterEffect},
                {3023, LabelType::EnterEffect},

                {3033, LabelType::Target_Anim},

                {2903, LabelType::Gradient},

                {1934, LabelType::SFX}, {3602, LabelType::SFX},

                {899, LabelType::Color},

                {1006, LabelType::PulseColor}
            };
        }
        case MapType::JSON: {
            parseMap();
        }
    }
}