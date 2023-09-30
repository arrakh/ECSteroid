//
// Created by Arya Rakha on 6/25/2023.
//

#ifndef ECSTEROID_DEBUGANGLESYSTEM_H
#define ECSTEROID_DEBUGANGLESYSTEM_H


#include "core/IRenderableSystem.h"
#include "../components/LocalPlayer.h"
#include "../components/WorldPosition.h"
#include "../components/Rotation.h"
#include "../components/debug/DebugAngle.h"

class DebugAngleSystem : public IRenderableSystem {
public:
    void Render(entt::registry *registry, sf::RenderTarget *renderTarget) override {
        auto view = registry->view<LocalPlayer, WorldPosition, Rotation>();
        for (auto [entity, pos, rot] : view.each()) {
            auto debug = registry->try_get<DebugAngle>(entity);
            if (debug == nullptr){
                float radius = 5.f;
                debug = new DebugAngle{new sf::CircleShape{radius}};
                debug->circle->setFillColor(sf::Color::Red);
                debug->circle->setOrigin(radius, radius);
            }

            float distance = 20.f;
            float rad = rot.value * M_PI / 180;
            Vector2 dir {cos(rad) * distance, sin(rad) * distance};

            debug->circle->setPosition(pos.vector + dir);

            renderTarget->draw(*debug->circle);
        }
    }

    int GetRenderOrder() override {
        return 100;
    }
};


#endif //ECSTEROID_DEBUGANGLESYSTEM_H
