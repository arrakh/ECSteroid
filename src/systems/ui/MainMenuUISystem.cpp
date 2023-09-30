//
// Created by Arya Rakha on 9/24/2023.
//

#include "MainMenuUISystem.h"
#include "../../components/WorldPosition.h"
#include "../../components/Sprite.h"
#include "../../components/ButtonObject.h"
#include "../../components/SFMLViewTarget.h"
#include "../EntityRelationSystem.h"
#include "../../components/SFMLText.h"
#include "../../application/Application.h"
#include "imgui.h"
#include "../../components/tween/TweenLocalPosition.h"
#include "../../components/tween/TweenEase.h"
#include "../../components/tween/TweenTimer.h"
#include "../../util/Tweens.h"


void MainMenuUISystem::CreateMainMenuButton(entt::registry *registry, Vector2 position, const std::string text, std::function<void()> callback) {
    auto button = registry->create();
    registry->emplace<SpriteDefinition>(button, SpriteDefinition {
            .spriteName =  "btn-normal", .initialOrder =  1,
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

    Tween::PositionOffset(registry, button, Vector2{0,500}, Vector2{0, 0}, 2.f)
        .SetEase(Ease::Type::OutCubic);

    auto childText = registry->create();
    EntityRelationSystem::Assign(registry, button, childText);

    registry->emplace<SFMLText>(childText, SFMLText {text, 52, sf::Color::White, "ethnocentric", 2} );
    registry->emplace<WorldPosition>(childText, WorldPosition {Vector2{0, 0}});
    registry->emplace<SFMLViewTarget>(childText, SFMLViewTarget{&uiView});

}

void MainMenuUISystem::Quit() {
    sfWindow->windowPtr->close();
}

void MainMenuUISystem::Play() {
    Application::ChangeScene<GameScene>();
}

void MainMenuUISystem::OnLoad(entt::registry *registry) {
    uiView.reset(sf::FloatRect{0, 0, sfWindow->width, sfWindow->height});
    uiView.setViewport(GetViewport());
    uiView.setCenter(0, 0);

    CreateMainMenuButton(registry, Vector2 {0, 100}, "Play", [this](){ this->Play();});
    CreateMainMenuButton(registry, Vector2 {0, 250}, "Quit", [this](){ this->Quit();});
}

void MainMenuUISystem::OnUnload() {

}

sf::FloatRect MainMenuUISystem::GetViewport() {
    return sf::FloatRect {0, 0, 1, 1};
}

sf::FloatRect rect;
Vector2 center{0, 0};
float rotation;

void MainMenuUISystem::Update(entt::registry *registry) {

    return;
    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);
    static bool windowOpen;
    if (!ImGui::Begin("Menu Tweaking", &windowOpen)){
        ImGui::End();
        return;
    }

    ImGui::SliderFloat("Viewport Rect Left", &rect.left, 0, 1);
    ImGui::SliderFloat("Viewport Rect Top", &rect.top, 0, 1);
    ImGui::SliderFloat("Viewport Rect Width", &rect.width, 0, 1);
    ImGui::SliderFloat("Viewport Rect Height", &rect.height, 0, 1);

    uiView.reset(sf::FloatRect{0, 0, sfWindow->width, sfWindow->height});

    uiView.setViewport(rect);

    ImGui::SliderFloat("Center X", &center.x, -1, 1);
    ImGui::SliderFloat("Center Y", &center.y, -1, 1);

    uiView.setCenter(center);

    ImGui::SliderFloat("Rotation", &rotation, 0, 360);
    uiView.setRotation(rotation);

    ImGui::End();
}
