//
// Created by Arya Rakha on 6/11/2023.
//

#ifndef CMAKESFMLPROJECT_SPRITEDEFINITION_H
#define CMAKESFMLPROJECT_SPRITEDEFINITION_H

#include <string>
#include "../datatype/Vector2.h"

struct SpriteDefinition {
    std::string spriteName;
    const int initialOrder = 0;
    const Vector2 pivot = Vector2{0.5f, 0.5f};

    const bool useCustomDimensions = false;
    const float customWidth = 0;
    const float customHeight = 0;

    const bool tiled = false;
    const float tiledScaleX = 1.f;
    const float tiledScaleY = 1.f;
};


#endif //CMAKESFMLPROJECT_SPRITEDEFINITION_H
