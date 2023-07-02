//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_POSITION_H
#define CMAKESFMLPROJECT_POSITION_H


#include "../datatype/Vector2.h"

struct Position {
public:
    Vector2 vector;

    [[nodiscard]] float getDistance(const Position& other) const {
        float deltaX = vector.x - other.vector.x;
        float deltaY = vector.y - other.vector.y;
        return std::sqrt(deltaX * deltaX + deltaY * deltaY);
    }
};


#endif //CMAKESFMLPROJECT_POSITION_H
