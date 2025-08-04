#pragma once

namespace GroupLabels {
    void update(LevelEditorLayer* editor);

    void updateLabelForTrigger(EffectGameObject* trigger);

    void getLabelInfoForTrigger(EffectGameObject* trigger);
    void getLabelFromInfo();
    cocos2d::CCLabelBMFont* getLabelNode(EffectGameObject* trigger);
}