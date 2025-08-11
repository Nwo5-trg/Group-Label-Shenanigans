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
    
    cocos2d::CCPoint getOffsetPos(GameObject* obj, bool extra);

    void updateLabelTypeMap();
    void updateExtrasColors();

    geode::Result<matjson::Value> parseJson(const char* path);

    void parseLabelTypeMap();
    void parseExtrasColors();
    
    cocos2d::ccColor3B jsonGetColor(const matjson::Value& value);
    unsigned int jsonGetUInt(const matjson::Value& value);
    float jsonGetFloat(const matjson::Value& value);

    inline std::unordered_map<int, LabelType> labelTypeMap;

    inline std::unordered_map<std::string, LabelType> labelTypeStringMap = {
        {"center", LabelType::Center}, 
        {"target_center", LabelType::Target_Center}, 
        {"target-center", LabelType::TargetCenter}, 
        {"item", LabelType::Item},
        {"item_anim", LabelType::Target_Anim}, 
        {"anim_target-center", LabelType::Anim_TargetCenter},
        {"target-center_item-item2", LabelType::TargetCenter_ItemItem2}, 
        {"target_item-item2", LabelType::Target_ItemItem2},
        {"item_target", LabelType::Item_Target}, 
        {"target_item", LabelType::Target_Item},
        {"gradient", LabelType::Gradient}, 
        {"enter", LabelType::EnterEffect},
        {"sfx", LabelType::SFX}, 
        {"color", LabelType::Color},
        {"pulsecolor", LabelType::PulseColor}
    };

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

    inline std::unordered_map<int, ExtrasType> extrasMap = {
        {1611, ExtrasType::Activate}, {1811, ExtrasType::Activate}, {1815, ExtrasType::Activate},

        {1595, ExtrasType::TouchToggle}, 

        {1616, ExtrasType::ControlID},
        
        {899, ExtrasType::Blending}, 
        
        {1006, ExtrasType::PulseTargetType}, 

        {1817, ExtrasType::Override}, 

        {1914, ExtrasType::Follow}
    };

    inline std::unordered_map<std::string, ExtrasType> extrasStringMap = {
        {"activate", ExtrasType::Activate},
        {"touch-toggle", ExtrasType::TouchToggle},
        {"control-id", ExtrasType::ControlID},
        {"blending", ExtrasType::Blending}, 
        {"pulse-target-type", ExtrasType::PulseTargetType}, 
        {"override", ExtrasType::Override}, 
        {"follow", ExtrasType::Follow}
    };

    inline std::unordered_map<ExtrasType, std::pair<std::pair<cocos2d::ccColor3B, float>, std::pair<cocos2d::ccColor3B, float>>> extrasColorMap;
}