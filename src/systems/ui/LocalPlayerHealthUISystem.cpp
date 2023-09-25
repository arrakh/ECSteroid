//
// Created by Arya Rakha on 7/8/2023.
//

#include "LocalPlayerHealthUISystem.h"
#include "../../components/LocalPlayer.h"
#include "../../components/Health.h"
#include "../../components/SFMLViewTarget.h"

void LocalPlayerHealthUISystem::Load(entt::registry *registry) {
    uiView.reset(sf::FloatRect{0, 0 , sfWindow->width, sfWindow->height});
    healthBar.setFillColor(sf::Color::Green);
    healthBgBar.setFillColor(sf::Color::Red);
    healthBgBar.setOutlineColor(sf::Color::White);
    healthBgBar.setOutlineThickness(2.f);

    healthBar.setSize(barSize);
    healthBgBar.setSize(barSize);

    healthBar.setOrigin(0.f, 0.f);
    healthBgBar.setOrigin(0.f, 0.f);

    healthBar.setPosition(barOffset);
    healthBgBar.setPosition(barOffset);


}

void LocalPlayerHealthUISystem::Unload() {

}

void LocalPlayerHealthUISystem::Render(entt::registry *registry) {
    auto window = sfWindow->windowPtr;
    auto originalView = window->getView();
    window->setView(uiView);

    auto view = registry->view<LocalPlayer, Health>();

    float total = 0.f;
    int counter = 0;
    for (auto [entity, health] : view.each()) {
        counter++;
        total += health.health / health.maxHealth;
    }

    float normalizedHealth = total / counter;

    healthBar.setSize(Vector2{barSize.x * normalizedHealth, barSize.y});
    healthBgBar.setSize(barSize);

    window->draw(healthBgBar);
    window->draw(healthBar);
    window->setView(originalView);
}

int LocalPlayerHealthUISystem::GetRenderOrder() {
    return 100;
}

