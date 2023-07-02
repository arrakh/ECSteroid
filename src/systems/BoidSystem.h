//
// Created by Arya Rakha on 7/1/2023.
//

#ifndef ECSTEROID_BOIDSYSTEM_H
#define ECSTEROID_BOIDSYSTEM_H


#include "core/IUpdatableSystem.h"
#include "../components/Boid.h"
#include "../components/Position.h"
#include "core/ILoadableSystem.h"

class BoidSystem : public IUpdatableSystem, public ILoadableSystem {
public:
    void Update(entt::registry *registry) override;

private:
public:
    void Unload() override;

public:
    void Load(entt::registry *registry) override;

private:
    void BounceOffWalls(entt::registry * registry, entt::entity entity, Boid& boid, Position& pos);
    Vector2 Flock(entt::registry * registry, Boid& boid, Position& pos, float distance, float power);
    Vector2 Align(entt::registry * registry, Boid& boid, Position& pos, float distance, float power);
    Vector2 Avoid(entt::registry * registry, Boid& boid, Position& pos, float distance, float power);
};


#endif //ECSTEROID_BOIDSYSTEM_H
