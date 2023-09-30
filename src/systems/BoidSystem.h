//
// Created by Arya Rakha on 7/1/2023.
//

#ifndef ECSTEROID_BOIDSYSTEM_H
#define ECSTEROID_BOIDSYSTEM_H


#include "core/IUpdatableSystem.h"
#include "../components/Boid.h"
#include "../components/WorldPosition.h"
#include "core/ILoadableSystem.h"
#include "core/IWindowInjectableSystem.h"
#include "../application/SFMLWindow.h"

class BoidSystem : public IUpdatableSystem, public IWindowInjectableSystem, public ILoadableSystem {
public:
    void Update(entt::registry *registry) override;

private:
public:
    void Unload() override;

public:
    void Load(entt::registry *registry) override;

    void OnInject(std::shared_ptr<IWindow> window) override { sfWindow = std::dynamic_pointer_cast<SFMLWindow>(window);}

private:
    std::shared_ptr<SFMLWindow> sfWindow;
    void BounceOffWalls(entt::registry * registry, entt::entity entity, Boid& boid, WorldPosition& pos);
    Vector2 Flock(entt::registry * registry, Boid& boid, WorldPosition& pos, float distance, float power);
    Vector2 Align(entt::registry * registry, Boid& boid, WorldPosition& pos, float distance, float power);
    Vector2 Avoid(entt::registry * registry, Boid& boid, WorldPosition& pos, float distance, float power);
};


#endif //ECSTEROID_BOIDSYSTEM_H
