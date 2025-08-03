#pragma once

namespace Cache {
    inline geode::Mod* mod;
    
    inline cocos2d::CCLayer* textObjectLayer;

    inline int currentLayer;
    inline int lastObjectCount;
    
    inline float layerAlphaMultiplier;

    // robtops effectgameobjects does store all triggers, so lemme make my own even if its a lil bit scuffed :3c
    inline std::vector<EffectGameObject*> triggers;

    inline std::unordered_map<EffectGameObject*, cocos2d::CCLabelBMFont*> labelMap;
    inline std::unordered_map<EffectGameObject*, int> groupMap;
    inline std::unordered_set<EffectGameObject*> updatedTriggers;
}