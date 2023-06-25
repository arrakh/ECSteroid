//
// Created by Arya Rakha on 6/10/2023.
//

#ifndef CMAKESFMLPROJECT_COLLISIONEVENT_H
#define CMAKESFMLPROJECT_COLLISIONEVENT_H


#include "entt/entity/entity.hpp"
#include "../systems/core/EventSystem.h"

struct CollisionEvent : public Event {
public:
    CollisionEvent(entt::entity a, entt::entity b) : a(a), b(b) {}

    entt::entity a;
    entt::entity b;
};


#endif //CMAKESFMLPROJECT_COLLISIONEVENT_H
