//
// Created by Arya Rakha on 6/25/2023.
//

#include "BulletLifetimeSystem.h"
#include "../components/bullet/BulletLifetime.h"
#include "../util/Time.h"

void BulletLifetimeSystem::Update(entt::registry *registry) {
    auto view = registry->view<BulletLifetime>();
    for (auto [entity, lifetime] : view.each()) {
        lifetime.time -= Time::deltaTime();
        if (lifetime.time <= 0.f) registry->destroy(entity);
    }
}
