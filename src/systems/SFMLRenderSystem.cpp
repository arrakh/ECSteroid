//
// Created by Arya Rakha on 6/4/2023.
//

#include <iostream>
#include "SFMLRenderSystem.h"
#include "../components/Position.h"
#include "../components/Rotation.h"
#include "../components/SFMLTransformable.h"
#include "../components/SFMLDrawable.h"
#include "../components/SFMLViewTarget.h"

void SFMLRenderSystem::Render(entt::registry* registry) {
    ApplyTransforms(registry);
    RenderDrawables(registry);
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
        if (rotData != nullptr) { t.transformable->setRotation(rotData->value); }
    }
}

void SFMLRenderSystem::RenderDrawables(entt::registry *registry) {
    registry->sort<SFMLDrawable>([](const SFMLDrawable& left, const SFMLDrawable& right){
        return left.order < right.order;
    });

    auto defaultView = sfWindow->windowPtr->getView();

    auto drawables = registry->view<SFMLDrawable>();
    for (auto [entity, comp] : drawables.each()) {
        auto viewTarget = registry->try_get<SFMLViewTarget>(entity);
        auto view = viewTarget != nullptr ? *viewTarget->targetView : defaultView;
        sfWindow->windowPtr->setView(view);
        sfWindow->windowPtr->draw(*comp.drawable);
    }



}

void SFMLRenderSystem::Load(entt::registry *registry) {
    registry->sort<SFMLTransformable, SFMLDrawable>();
    registry->sort<SFMLDrawable, SFMLViewTarget>();
}

void SFMLRenderSystem::Unload() {

}
