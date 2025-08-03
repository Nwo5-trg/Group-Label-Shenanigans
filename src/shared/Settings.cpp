#include "Settings.hpp"
#include "Cache.hpp"

using namespace geode::prelude;
using namespace Settings;

void Settings::updateSettings() {
    Cache::mod = Mod::get();

    set(rotate, "rotate");
    set(hide0Group, "hide-0-group");
    
    set(opacity, "opacity");
    set(scale, "scale");
    set(layerAlphaMultiplier, "layer-alpha-multiplier");
    set(xOff, "x-off");
    set(yOff, "y-off");
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

$on_mod(Loaded) {
    updateSettings();
    
    listenForAllSettingChangesV3([] (std::shared_ptr<geode::SettingV3>){
        updateSettings();
    });
}