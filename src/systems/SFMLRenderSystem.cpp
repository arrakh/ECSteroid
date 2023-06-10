//
// Created by Arya Rakha on 6/4/2023.
//

#include <iostream>
#include "SFMLRenderSystem.h"
#include "../components/Position.h"
#include "../components/Rotation.h"
#include "../components/SFMLTransformable.h"
#include "../components/SFMLDrawable.h"

void SFMLRenderSystem::Render(entt::registry* registry, sf::RenderTarget* renderTarget) {
    ApplyTransforms(registry);
    RenderDrawables(registry, renderTarget);
}

int SFMLRenderSystem::GetRenderOrder() {
    return 0;
}

void SFMLRenderSystem::ApplyTransforms(entt::registry *registry) {
    auto view = registry->view<SFMLTransformable>();

    for (auto [entity, t] : view.each()) {

        auto posData = registry->try_get<Position>(entity);
        if (posData != nullptr) t.transformable->setPosition(posData->vector.x, posData->vector.y);

        auto rotData = registry->try_get<Rotation>(entity);
        if (rotData != nullptr) t.transformable->setRotation(rotData->value);

        auto id = static_cast<uintptr_t>(entity);
        auto pos = t.transformable->getPosition();
    }
}

void SFMLRenderSystem::RenderDrawables(entt::registry *registry, sf::RenderTarget *target) {
    registry->sort<SFMLDrawable>([](const SFMLDrawable& left, const SFMLDrawable& right){
        return left.order < right.order;
    });

    auto view = registry->view<SFMLDrawable>();
    for (auto [entity, comp] : view.each()) {
        target->draw(*comp.drawable);
    }
}

void SFMLRenderSystem::Load(entt::registry *registry) {
    registry->sort<SFMLTransformable, SFMLDrawable>();
}

void SFMLRenderSystem::Unload() {

}
