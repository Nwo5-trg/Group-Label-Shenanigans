#pragma once
#include "Constants.hpp"
#include "Enums.hpp"

namespace Utils {
    cocos2d::CCPoint rotatePoint(cocos2d::CCPoint pos, cocos2d::CCPoint pivot, float rad);

    std::unordered_set<int> parseIntArray(const std::string& input);
    
    cocos2d::CCPoint getTriggerBodyPos(GameObject* obj);

    int getTriggerGroup(EffectGameObject* trigger);

    inline std::unordered_map<int, LabelType> labelTypeMap = {
        {1817, LabelType::ItemID}, {3641, LabelType::ItemID}, {3614, LabelType::ItemID},
        {3615, LabelType::ItemID}, {3617, LabelType::ItemID},

        {1914, LabelType::CenterGroup}, {2914, LabelType::CenterGroup},

        {22, LabelType::EnterEffect}, {24, LabelType::EnterEffect}, {23, LabelType::EnterEffect},
        {25, LabelType::EnterEffect}, {26, LabelType::EnterEffect}, {27, LabelType::EnterEffect},
        {28, LabelType::EnterEffect}, {55, LabelType::EnterEffect}, {56, LabelType::EnterEffect},
        {57, LabelType::EnterEffect}, {58, LabelType::EnterEffect}, {59, LabelType::EnterEffect},
        {1915, LabelType::EnterEffect}, {3017, LabelType::EnterEffect}, {3019, LabelType::EnterEffect},
        {3018, LabelType::EnterEffect}, {3020, LabelType::EnterEffect}, {3021, LabelType::EnterEffect},
        {3023, LabelType::EnterEffect},

        {1934, LabelType::SFXID}, {3602, LabelType::SFXID},

        {899, LabelType::ColorChannel},

        {3033, LabelType::AnimationID},

        {2903, LabelType::GradientID}
    };

    inline std::unordered_set<int> triggerBlacklist = {
        1913, 2015, 2925, 1916, 2901, 2999, 3606, 1935, 2068, 3607, 2900, 1917,
        3612, 33, 32, 1613, 1612, 1818, 1819, 1932, 2899, 2066, 2904, 2905, 2907,
        2909, 2910, 2911, 2912, 2916, 2917, 2920, 2921, 2922, 2923, 2924, 1520,
        3029, 3030, 3031, 31
    };

    inline std::unordered_set<int> triggerWhitelist;
}