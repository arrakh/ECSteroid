//
// Created by Arya Rakha on 6/4/2023.
//

#include <iostream>
#include "RectangleDrawSystem.h"
#include "../components/Position.h"
#include "../components/SFMLRectShape.h"
#include "../components/Rotation.h"

void RectangleDrawSystem::Render(entt::registry* registry, sf::RenderTarget* renderTarget) {
    auto view = registry->view<SFMLRectShape>();

    for (auto [entity, shape] : view.each()) {

        auto posData = registry->try_get<Position>(entity);
        if (posData != nullptr) shape.shape.setPosition(posData->vector.x, posData->vector.y);

        auto rotData = registry->try_get<Rotation>(entity);
        if (rotData != nullptr) shape.shape.setRotation(rotData->value);
        
        renderTarget->draw(shape.shape);
    }
}

int RectangleDrawSystem::GetRenderOrder() {
    return 0;
}

void RectangleDrawSystem::RegisterEvents(entt::registry *registry, Events::Listener *listener) {
    listener->Subscribe<TestEvent>(RectangleDrawSystem::TestFunc);
}

void RectangleDrawSystem::UnregisterEvents(entt::registry *registry, Events::Listener *listener) {
    listener->Unsubscribe<TestEvent>(RectangleDrawSystem::TestFunc);
}

void RectangleDrawSystem::TestFunc(const TestEvent& event){
    std::cout << "GOT EVENT v: " << event.value << " fv: " << event.fValue << std::endl;
}
