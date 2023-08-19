//
// Created by Arya Rakha on 7/9/2023.
//

#include "GameOverTextUISystem.h"
#include "../../application/Application.h"
#include "../../components/LocalPlayer.h"
#include "../../util/Time.h"
#include "../../datatype/Vector2.h"
#include "imgui.h"
#include <cmath>
#include <iostream>

void GameOverTextUISystem::Load(entt::registry *registry) {
    uiView.reset(sf::FloatRect{0, 0 , sfWindow->width, sfWindow->height});

    Vector2 bgSize {99999, 99999};
    blackBg.setFillColor(sf::Color{0, 0, 0, 0});
    blackBg.setOrigin(bgSize / 2.f);
    blackBg.setSize(bgSize);

    gameOverText.setFont(*fontService->Get("ethnocentric"));
    gameOverText.setCharacterSize(72);
    gameOverText.setString("Game Over");
    gameOverText.setFillColor(sf::Color{255, 255, 255, 255});

    auto bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
    gameOverText.setPosition(sfWindow->width / 2.f, sfWindow->height / 2.f - 100);
}

void GameOverTextUISystem::Unload() {

}

Vector2 origins{0.0f, 0.0f};
Vector2 pos {0.0f, 0.0f};

void GameOverTextUISystem::Render(entt::registry *registry) {
    if (!isGameOver) return;
    auto window = sfWindow->windowPtr;
    auto originalView = window->getView();
    window->setView(uiView);

    alphaProgress += Time::deltaTime() / animateDuration;
    if (alphaProgress >= 1.f) alphaProgress = 1.f;

    int blackAlpha = std::ceil(180.f * alphaProgress);
    blackBg.setFillColor(sf::Color{0, 0, 0, static_cast<sf::Uint8>(blackAlpha)});

    int textAlpha = std::ceil(255.f * alphaProgress);
    gameOverText.setFillColor(sf::Color{255, 255, 255, static_cast<sf::Uint8>(textAlpha)});

    window->draw(blackBg);
    window->draw(gameOverText);
    window->setView(originalView);
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

void GameOverTextUISystem::LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) {
    fontService = serviceLocator->Locate<SFMLFontService>();
}
