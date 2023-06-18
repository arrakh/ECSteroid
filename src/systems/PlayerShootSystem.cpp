//
// Created by rafizidny on 6/18/2023.
//

#include "PlayerShootSystem.h"
#include "../components/ShootAbility.h"
#include "../components/LocalPlayer.h"
#include <SFML/Graphics.hpp>

void PlayerShootSystem::Update(entt::registry *registry) {

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return;

    auto view = registry->view<ShootAbility, LocalPlayer>();
    for (auto [entity, shootData] : view.each()) {
        bool onCooldown = registry->all_of<ShootAbilityCooldown>(entity);
        if (onCooldown) return;

    }
}
