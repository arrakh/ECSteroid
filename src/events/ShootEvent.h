//
// Created by Arya Rakha on 10/8/2023.
//

#ifndef ECSTEROID_SHOOTEVENT_H
#define ECSTEROID_SHOOTEVENT_H

#include "../systems/core/EventSystem.h"
#include "entt/entity/entity.hpp"
#include "../components/ShootAbility.h"

class ShootEvent : public Event {
public:
    entt::registry *registry;

    ShootEvent(entt::registry *registry, entt::entity shooter, const Vector2 &position, float rotation,
               const ShootAbility &abilityData) : registry(registry), shooter(shooter), position(position),
                                                  rotation(rotation), abilityData(abilityData) {}

    entt::entity shooter;
    Vector2 position;
    float rotation;
    const ShootAbility abilityData;
};

#endif //ECSTEROID_SHOOTEVENT_H
