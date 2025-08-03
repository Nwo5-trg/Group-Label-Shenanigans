#pragma once

namespace GroupLabels {
    void update(LevelEditorLayer* editor);

    void updateLayerAlpha(GameObject* obj);
    cocos2d::CCLabelBMFont* getLabel(EffectGameObject* trigger);
}