//
// Created by Arya Rakha on 7/9/2023.
//

#include "GameOverTextUISystem.h"
#include "../../Application.h"
#include "../../components/LocalPlayer.h"
#include "../../util/Time.h"
#include "../../datatype/Vector2.h"
#include <cmath>
#include <iostream>

void GameOverTextUISystem::Load(entt::registry *registry) {
    uiView.setViewport(sf::FloatRect{0, 0 ,1 ,1});

    Vector2 bgSize {99999, 99999};
    blackBg.setFillColor(sf::Color{0, 0, 0, 0});
    blackBg.setOrigin(bgSize / 2.f);
    blackBg.setSize(bgSize);

    //should be a font service
    if (!gameOverFont.loadFromFile("assets/fonts/ethnocentric.otf"))
        throw std::invalid_argument("COULD NOT FIND FONT");

    gameOverText.setFont(gameOverFont);
    gameOverText.setCharacterSize(72);
    gameOverText.setString("Game Over");
    gameOverText.setFillColor(sf::Color{255, 255, 255, 0});
}

void GameOverTextUISystem::Unload() {

}

void GameOverTextUISystem::Render(entt::registry *registry, sf::RenderTarget *renderTarget) {
    if (!isGameOver) return;
    auto window = Application::WindowPtr;
    auto originalView = window->getView();
    renderTarget->setView(uiView);

    alphaProgress += Time::deltaTime() / animateDuration;
    std::cout << "alpha progress is now " << alphaProgress << std::endl;
    if (alphaProgress >= 1.f) alphaProgress = 1.f;

    int blackAlpha = std::ceil(78.f * alphaProgress);
    blackBg.setFillColor(sf::Color{0, 0, 0, static_cast<sf::Uint8>(blackAlpha)});

    int textAlpha = std::ceil(255.f * alphaProgress);
    gameOverText.setFillColor(sf::Color{255, 255, 255, static_cast<sf::Uint8>(textAlpha)});

    renderTarget->setView(originalView);
}

int GameOverTextUISystem::GetRenderOrder() {
    return 600;
}

void GameOverTextUISystem::SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    registry->on_destroy<LocalPlayer>().connect<&GameOverTextUISystem::OnLocalPlayerDestroyed>(this);
}

void GameOverTextUISystem::UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    registry->on_destroy<LocalPlayer>().disconnect<&GameOverTextUISystem::OnLocalPlayerDestroyed>(this);
}

void GameOverTextUISystem::OnLocalPlayerDestroyed() {
    std::cout << "GAME OVER!!!\n";
    isGameOver = true;
}
