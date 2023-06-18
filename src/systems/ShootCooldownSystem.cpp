//
// Created by rafizidny on 6/18/2023.
//

#include "ShootCooldownSystem.h"
#include "../components/ShootAbility.h"
#include "../util/Time.h"

void ShootCooldownSystem::Update(entt::registry *registry) {
    auto view = registry->view<ShootAbilityCooldown>();
    for (auto [entity, cooldown] : view.each()) {
        auto newValue = cooldown.value - Time::deltaTime();
        if (newValue <= 0.f) registry->remove<ShootAbilityCooldown>(entity);
        else registry->patch<ShootAbilityCooldown>(entity, [newValue](auto data){
            data.value = newValue;
        });
    }
}
