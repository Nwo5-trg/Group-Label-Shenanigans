#pragma once
#include "Constants.hpp"
#include "Types.hpp"

#define TO_CHARS(ptr, num) ((ptr) = std::to_chars((ptr), Cache::labelCharBuffer + Constants::labelCharBufferSize, (num)).ptr)
#define TO_CHARS_COL(ptr, num) ((ptr) = Utils::to_chars_col((ptr), Cache::labelCharBuffer + Constants::labelCharBufferSize, (num)))
#define ADD_CHAR(ptr, chr) (*(ptr)++ = (chr))

namespace Utils {
    cocos2d::CCPoint rotatePoint(cocos2d::CCPoint pos, cocos2d::CCPoint pivot, float rad);

    std::unordered_set<int> parseIntArray(const std::string& input);

    char* to_chars_col(char* first, char* last, int value);
    
    cocos2d::CCPoint getTriggerBodyPos(GameObject* obj);

    void updateLayerAlpha(GameObject* obj);

    void updateLabelTypeMap();

    inline std::unordered_map<int, LabelType> labelTypeMap;

    inline std::unordered_set<int> triggerBlacklist = {
        1913, 2015, 2925, 1916, 2901, 2999, 3606, 1935, 2068, 3607, 2900, 1917,
        3612, 33, 32, 1613, 1612, 1818, 1819, 1932, 2899, 2066, 2904, 2905, 2907,
        2909, 2910, 2911, 2912, 2916, 2917, 2920, 2921, 2922, 2923, 2924, 1520,
        3029, 3030, 3031, 31
    };

    inline std::unordered_set<int> centeredTriggersList = {
        3640, 22, 24, 23, 25, 26, 27, 28, 55, 56, 57, 58, 59, 1915, 3017, 3019, 
        3018, 3020, 3021, 3023
    };

    inline std::unordered_map<int, const char*> colorConversionsMap = {
        {1004, "obj"}, {1000, "bg"}, {1001, "g1"}, {1009, "g2"},
        {1013, "mg"}, {1014, "mg2"}, {1002, "line"}, {1003, "3dl"},
        {1005, "p1"}, {1006, "p2"}, {1007, "lbg"}, {1010, "black"},
        {1011, "white"}, {1012, "lighter"}
    };
}