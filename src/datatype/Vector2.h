//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_VECTOR2_H
#define CMAKESFMLPROJECT_VECTOR2_H

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

struct Vector2 {
    float x, y;

    Vector2(){}

    Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
    Vector2(sf::Vector2f v) : x(v.x), y(v.y) {}
    Vector2(b2Vec2 v) : x(v.x), y(v.y) {}

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
};


#endif //CMAKESFMLPROJECT_VECTOR2_H
