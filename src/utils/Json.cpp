#include "Utils.hpp"
#include "../shared/Cache.hpp"

using namespace geode::prelude;
using namespace Utils;

geode::Result<matjson::Value> Utils::parseJson(const char* path) {
    auto filePath = string::pathToString(Cache::mod->getConfigDir() / path);
    if (!std::filesystem::exists(filePath)) return Err("no file");

    std::ifstream file(filePath);
    auto parseJson = matjson::parse(file);
    if (!parseJson) return Err("failed to parse");

    auto json = parseJson.unwrap();
    if (!json.isObject()) return Err("not obj");

    return Ok(json);
}

void Utils::parseLabelTypeMap() {
    labelTypeMap.clear();
    triggerBlacklist.clear();

    // idk how to use geode results properly and i dont wanna read
    auto labelTypesRes = parseJson("label-types.json");
    if (!labelTypesRes) {
        log::error("{}", labelTypesRes.err());
        return;
    }

    auto json = labelTypesRes.unwrap();
    for (auto [id, value] : json) {
        int trigger = std::strtol(id.c_str(), nullptr, 10);

        if (value.contains("type") && value["type"].isString()) {
            auto type = value["type"].asString().unwrap();

            if (type == "blacklist") {
                triggerBlacklist.insert(trigger);
            } else if (labelTypeStringMap.contains(type)) {
                labelTypeMap[trigger] = labelTypeStringMap[type];
            }
        }
    }
}
void Utils::parseExtrasColors() {
    // idk how to use geode results properly and i dont wanna read
    auto extrasColorsRes = parseJson("extras-colors.json");
    if (!extrasColorsRes) {
        log::error("{}", extrasColorsRes.err());
        return;
    }

    auto json = extrasColorsRes.unwrap();
    for (auto [id, value] : json) {
        if (!extrasStringMap.contains(id)) continue;
        auto type = extrasStringMap[id];

        if (
            !(value.contains("off-color") && value["off-color"].isArray())
            || !(value.contains("off-opacity") && value["off-opacity"].isNumber())
            || !(value.contains("on-color") && value["on-color"].isArray())
            || !(value.contains("on-opacity") && value["on-opacity"].isNumber())
        ) continue;

        auto offColor = value["off-color"].asArray().unwrap();
        auto offOpacity = value["off-opacity"].asDouble().unwrap();
        auto onColor = value["on-color"].asArray().unwrap();
        auto onOpacity = value["on-opacity"].asDouble().unwrap();

        extrasColorMap[type] = {
            {jsonGetColor(offColor), jsonGetFloat(offOpacity)},
            {jsonGetColor(onColor), jsonGetFloat(onOpacity)}
        };
    }
}

ccColor3B Utils::jsonGetColor(const matjson::Value& value) {
    if (!value.isArray()) return {};
    auto col = value.asArray().unwrap();
    if (col.size() != 3) return {};
    return ccc3(
        jsonGetUInt(col[0]),
        jsonGetUInt(col[1]),
        jsonGetUInt(col[2])
    );
}
unsigned int Utils::jsonGetUInt(const matjson::Value& value) {
    if (value.isExactlyUInt()) return value.asUInt().unwrap();
    return 0.0f;
}
float Utils::jsonGetFloat(const matjson::Value& value) {
    if (value.isNumber()) return value.asDouble().unwrap();
    return 0.0f;
}