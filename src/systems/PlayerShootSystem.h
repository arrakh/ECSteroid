//
// Created by rafizidny on 6/18/2023.
//

#ifndef ECSTEROID_PLAYERSHOOTSYSTEM_H
#define ECSTEROID_PLAYERSHOOTSYSTEM_H


#include "core/IUpdatableSystem.h"
#include "core/ILoadableSystem.h"
#include "../datatype/Vector2.h"
#include "../components/ShootAbility.h"
#include "core/IEventPublisherSystem.h"

class PlayerShootSystem: public IUpdatableSystem, public ILoadableSystem, public IEventPublisherSystem {
public:
    void Update(entt::registry *registry) override;

    void Load(entt::registry *registry) override;

    void Unload() override;

    void OnInjectPublisher(Events::Publisher *pub) override {publisher = pub;}

private:
    Events::Publisher *publisher;

    void CreateBullet(entt::entity shooter, entt::registry *registry, Vector2 pos, float angle, ShootAbility data);
    void CreateMuzzleFlash(entt::entity shooter, entt::registry *registry, Vector2 pos, float angle, ShootAbility data);
};


#endif //ECSTEROID_PLAYERSHOOTSYSTEM_H
