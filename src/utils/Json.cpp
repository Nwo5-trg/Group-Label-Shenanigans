#include "Utils.hpp"
#include "../shared/Cache.hpp"

using namespace geode::prelude;
using namespace Utils;

void Utils::parseMap() {
    labelTypeMap.clear();
    triggerBlacklist.clear();

    auto path = string::pathToString(Cache::mod->getConfigDir() / "label-types.json");
    if (!std::filesystem::exists(path)) return;

    std::ifstream file(path);
    auto parseJson = matjson::parse(file);
    if (!parseJson.isOk()) return;

    auto json = parseJson.unwrap();
    if (!json.isObject()) return;
    for (auto [id, value] : json) {
        int trigger = std::strtol(id.c_str(), nullptr, 10);

        if (value.contains("type") && value["type"].isString()) {
            auto type = value["type"].asString().unwrap();

            if (type == "blacklist") {
                triggerBlacklist.insert(trigger);
            } else if (labelTypeStringMap.contains(type)) {
                labelTypeMap.insert({trigger, labelTypeStringMap[type]});
            }
        }
    }
}