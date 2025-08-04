#pragma once

#include "../utils/Types.hpp"

namespace Cache {
    inline geode::Mod* mod;
    
    inline cocos2d::CCLayer* textObjectLayer;

    inline int currentLayer;
    inline int lastObjectCount;
    inline int layerAlpha;

    // in my search for the fastest way to convert shit to a string we are going c style :3
    // (this is an awful idea and a direct result of my laziness)
    inline char labelCharBuffer[48]; // should be enough
    inline char* labelCharBufferEnd;

    inline TriggerLabelInfo labelInfo;
    
    // robtops effectgameobjects does store all triggers, so lemme make my own even if its a lil bit scuffed :3c
    inline std::vector<EffectGameObject*> triggers;

    inline std::unordered_map<EffectGameObject*, cocos2d::CCLabelBMFont*> labelMap;
    inline std::unordered_map<EffectGameObject*, TriggerLabelInfo> labelInfoMap;
    inline std::unordered_set<EffectGameObject*> updatedTriggers;

    namespace View {
        inline float zoom;
        inline float cullDistance;
        inline cocos2d::CCSize size;
        inline cocos2d::CCPoint relativeCenter; // to batchlayer
    }
}