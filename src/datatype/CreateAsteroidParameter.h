//
// Created by Arya Rakha on 8/12/2023.
//

#ifndef ECSTEROID_CREATEASTEROIDPARAMETER_H
#define ECSTEROID_CREATEASTEROIDPARAMETER_H


#include "../components/Asteroid.h"
#include "Vector2.h"

class CreateAsteroidParameter {
public:
    const Asteroid definition;
    const Vector2 position;
    const Vector2 direction;
};


#endif //ECSTEROID_CREATEASTEROIDPARAMETER_H
