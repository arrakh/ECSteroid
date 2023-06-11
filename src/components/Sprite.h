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
    const float initialAngle = 0.f;
    const float initialScale = 1.f;
    const bool center = true;
};


#endif //CMAKESFMLPROJECT_SPRITEDEFINITION_H
