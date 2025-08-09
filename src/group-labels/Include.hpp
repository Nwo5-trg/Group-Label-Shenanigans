#pragma once

namespace GroupLabels {
    void update(LevelEditorLayer* editor);

    void updateLabelForTrigger(EffectGameObject* trigger);
    void cullUnused(std::unordered_map<EffectGameObject*, cocos2d::CCLabelBMFont*>& vector, bool extra);

    void getLabelInfoForTrigger(EffectGameObject* trigger);
    void getLabelFromInfo();
    cocos2d::CCLabelBMFont* getLabelNode(EffectGameObject* trigger);

    cocos2d::CCLabelBMFont* getExtrasNode(EffectGameObject* trigger);
    void updateExtrasColor(cocos2d::CCLabelBMFont* extra, EffectGameObject* trigger);
}