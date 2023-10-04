//
// Created by Arya Rakha on 7/9/2023.
//

#include "GameOverTextUISystem.h"
#include "../../application/Application.h"
#include "../../components/LocalPlayer.h"
#include "../../util/Time.h"
#include "../../datatype/Vector2.h"
#include "imgui.h"
#include "../../components/Sprite.h"
#include "../../components/ButtonObject.h"
#include "../../components/SFMLViewTarget.h"
#include "../../components/WorldPosition.h"
#include "../EntityRelationSystem.h"
#include "../../components/SFMLText.h"
#include "../../scenes/MenuScene.h"
#include "../../components/SFMLDrawable.h"
#include "../../components/debug/DebugName.h"
#include <cmath>
#include <iostream>

void GameOverTextUISystem::Load(entt::registry *registry) {
    uiView.reset(sf::FloatRect{0, 0 , sfWindow->width, sfWindow->height});
    uiView.setViewport(sf::FloatRect{0, 0, 1, 1});
    uiView.setCenter(0, 0);

}

void GameOverTextUISystem::Unload() {

}

void GameOverTextUISystem::CreateButton(entt::registry *registry, Vector2 position, const std::string text, std::function<void()> callback) {
    auto button = registry->create();
    registry->emplace<SpriteDefinition>(button, SpriteDefinition {
            .spriteName =  "btn-normal", .initialOrder =  701,
            .useCustomDimensions = true, .customWidth = 300, .customHeight = 80
    });

    registry->emplace<Button>(button, Button {.size = Vector2{300, 80}, .callback = callback});

    registry->emplace<WorldPosition>(button, WorldPosition {position });

    registry->emplace<SFMLViewTarget>(button, SFMLViewTarget{&uiView});

    registry->emplace<ButtonStateSpritesDefinition>(button, ButtonStateSpritesDefinition {
            .normalSpriteName = "btn-normal",
            .highlightedSpriteName = "btn-hover",
            .pressedSpriteName = "btn-pressed"
    });

    auto childText = registry->create();
    EntityRelationSystem::Assign(registry, button, childText);

    registry->emplace<SFMLText>(childText, SFMLText {text, 52, sf::Color::White, "ethnocentric", 702} );
    registry->emplace<WorldPosition>(childText, WorldPosition {Vector2{0, 0}});
    registry->emplace<SFMLViewTarget>(childText, SFMLViewTarget{&uiView});

}

void GameOverTextUISystem::SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    registry->on_destroy<LocalPlayer>().connect<&GameOverTextUISystem::OnLocalPlayerDestroyed>(this);
}

void GameOverTextUISystem::UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    registry->on_destroy<LocalPlayer>().disconnect<&GameOverTextUISystem::OnLocalPlayerDestroyed>(this);
}

void GameOverTextUISystem::OnLocalPlayerDestroyed(entt::registry &registry, entt::entity entity) {
    std::cout << "GAME OVER!!!\n";
    isGameOver = true;

    CreateButton(&registry, Vector2(0, 120), "Retry", [](){ Application::ChangeScene<GameScene>(); });
    CreateButton(&registry, Vector2(0, 220), "Quit", [](){ Application::ChangeScene<MenuScene>(); });

    blackBg = registry.create();
    Vector2 bgSize {99999, 99999};
    auto bg = std::make_shared<sf::RectangleShape>();
    bg->setSize(bgSize);
    bg->setFillColor(sf::Color{0, 0, 0, 0});
    bg->setPosition(0, 0);
    bg->setOrigin(bgSize / 2.f);
    registry.emplace<SFMLDrawable>(blackBg, SFMLDrawable {2, bg});
    registry.emplace<SFMLViewTarget>(blackBg, SFMLViewTarget{&uiView});

    text = registry.create();
    registry.emplace<SFMLText>(text, SFMLText {"Game Over", 72, sf::Color::Transparent, "ethnocentric", 3});
    registry.emplace<WorldPosition>(text, WorldPosition{Vector2{0, -100}});
    registry.emplace<SFMLViewTarget>(text, SFMLViewTarget{&uiView});
}