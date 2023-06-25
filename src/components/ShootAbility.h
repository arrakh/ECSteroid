//
// Created by rafizidny on 6/18/2023.
//

#ifndef ECSTEROID_SHOOTABILITY_H
#define ECSTEROID_SHOOTABILITY_H

#include "../datatype/Vector2.h"

struct ShootAbility {
public:
    float startDistance;
    float cooldown;
    float bulletSpeed;
    float bulletLifetime;
    float bulletDamage;
};

struct ShootAbilityCooldown{
public:
    float value;
};



#endif //ECSTEROID_SHOOTABILITY_H
