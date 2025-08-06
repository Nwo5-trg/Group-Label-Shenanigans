#include "Settings.hpp"
#include "Cache.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;
using namespace Settings;

void Settings::updateSettings() {
    Cache::mod = Mod::get();

    set(rotate, "rotate");
    set(hide0Group, "hide-0-group");
    auto info = Cache::mod->getSettingValue<std::string>("more-label-info");
    if (info == "More Label Info") moreLabelInfo = MapType::MoreLabelInfo;
    else if (info == "Vanilla") moreLabelInfo = MapType::Vanilla;
    else moreLabelInfo = MapType::JSON;
    
    set(opacity, "opacity");
    set(scale, "scale");
    set(widthLimit, "width-limit");
    set(layerAlphaMultiplier, "layer-alpha-multiplier");
    set(xOff, "x-off");
    set(yOff, "y-off");

    set(triggerWhitelist, "trigger-whitelist");

    Utils::updateLabelTypeMap();
}

void Settings::set(bool& setting, const char* key) {
    setting = Cache::mod->getSettingValue<bool>(key);
}
void Settings::set(int& setting, const char* key) {
    setting = Cache::mod->getSettingValue<int64_t>(key);
}
void Settings::set(float& setting, const char* key) {
    setting = Cache::mod->getSettingValue<double>(key);
}
void Settings::set(std::unordered_set<int>& setting, const char* key) {
    setting = Utils::parseIntArray(Cache::mod->getSettingValue<std::string>(key));
}

$on_mod(Loaded) {
    updateSettings();
    
    listenForAllSettingChangesV3([] (std::shared_ptr<geode::SettingV3>){
        updateSettings();
    });
}