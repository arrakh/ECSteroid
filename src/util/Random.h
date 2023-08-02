//
// Created by Arya Rakha on 6/30/2023.
//

#ifndef ECSTEROID_RANDOM_H
#define ECSTEROID_RANDOM_H


#include <random>
#include "../datatype/Vector2.h"

class Random {
public:
    static float Range(float min, float max) {
        std::uniform_real_distribution<float> rand(min,max);
        return rand(rng);
    }

    static int Range(int min, int max) {
        std::uniform_int_distribution<int> rand(min, max);
        return rand(rng);
    }

    static const Vector2 UnitCircle() {
        std::uniform_real_distribution<float> rand(0.f, 360.f);
        float randRadian = rand(rng) * M_PI / 180;
        return Vector2 {cos(randRadian), sin(randRadian)};
    }

private:
    static std::mt19937 rng;
    static std::random_device dev;
};

#endif //ECSTEROID_RANDOM_H
