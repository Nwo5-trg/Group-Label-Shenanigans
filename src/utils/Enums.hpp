#pragma once

enum class LabelType {
    Target,
    Center,
    Target_Center,
    TargetCenter,
    Item,
    Target_Anim,
    Anim_TargetCenter,
    TargetCenter_ItemItem2,
    Target_ItemItem2,
    Item_Target,
    Target_Item,
    Gradient,
    EnterEffect,
    SFX,
    Color,
    PulseColor
};

enum class ExtrasType {
    Activate,
    TouchToggle,
    ControlID,
    Blending,
    PulseTargetType,
    Override,
    Follow
};

enum class MapType {
    MoreLabelInfo,
    Vanilla,
    JSON
};