//
// Created by Arya Rakha on 7/1/2023.
//

#ifndef ECSTEROID_ENTITYDEATHEVENT_H
#define ECSTEROID_ENTITYDEATHEVENT_H


#include "../systems/core/EventSystem.h"
#include "entt/entity/entity.hpp"

class EntityDeathEvent : public Event {
public:
    explicit EntityDeathEvent(entt::entity entity) : entity(entity) {}

    entt::entity entity;
};


#endif //ECSTEROID_ENTITYDEATHEVENT_H
