#pragma once

enum class MapType;

namespace Settings {
    inline bool rotate;
    inline bool hide0Group;

    inline MapType moreLabelInfo;
    
    inline float opacity;
    inline float scale;
    inline float widthLimit;
    inline float layerAlphaMultiplier;
    inline float xOff;
    inline float yOff;

    inline std::unordered_set<int> triggerWhitelist;
    
    void updateSettings();

    void set(bool& setting, const char* key);
    void set(int& setting, const char* key);
    void set(float& setting, const char* key);
    void set(std::unordered_set<int>& setting, const char* key);
}