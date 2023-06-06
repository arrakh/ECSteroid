//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_VECTOR2_H
#define CMAKESFMLPROJECT_VECTOR2_H

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

struct Vector2 {
    constexpr static const float B2_SCALE_FACTOR = 0.01f;

    float x, y;

    Vector2() : x(), y(){}

    Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
    explicit Vector2(sf::Vector2f v) : x(v.x), y(v.y) {}
    explicit Vector2(b2Vec2 v) : x(v.x / B2_SCALE_FACTOR), y(v.y / B2_SCALE_FACTOR) {}

    operator sf::Vector2f() const { return sf::Vector2f(x, y); }
    operator b2Vec2() const { return b2Vec2(x * B2_SCALE_FACTOR, y * B2_SCALE_FACTOR); }

    Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
    Vector2 operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }

    Vector2& operator=(const Vector2& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
};


#endif //CMAKESFMLPROJECT_VECTOR2_H
