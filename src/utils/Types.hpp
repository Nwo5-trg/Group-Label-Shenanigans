#pragma once

#include "Enums.hpp"

struct TriggerLabelInfo {
    LabelType type = LabelType::Target;
    
    int target = -1;
    int ext = -1;
    int center = -1;
    int ext2 = -1;

    TriggerLabelInfo() = default;

    void reset(LabelType ty) {
        type = ty;
        target = -1; ext = -1;
        center = -1; ext2 = -1;
    }

    bool operator==(const TriggerLabelInfo& other) const {
        return target == other.target && ext == other.ext 
        && center == other.center && ext2 == other.ext2;
    }

    bool operator==(int other) const {
        return target == other && ext == other 
        && center == other && ext2 == other;
    }
};