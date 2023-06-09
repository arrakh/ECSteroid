//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_RECTANGLEDRAWSYSTEM_H
#define CMAKESFMLPROJECT_RECTANGLEDRAWSYSTEM_H

#include "core/IRenderableSystem.h"
#include "core/IEventRegistrableSystem.h"
#include "../events/TestEvent.h"

class RectangleDrawSystem : public IRenderableSystem, public IEventRegistrableSystem {
public:
    void Render(entt::registry* registry, sf::RenderTarget* renderTarget) override;

    void RegisterEvents(entt::registry *registry, Events::Listener *listener) override;

    void UnregisterEvents(entt::registry *registry, Events::Listener *listener) override;

    int GetRenderOrder() override;

    static void TestFunc(const TestEvent& event);
};


#endif //CMAKESFMLPROJECT_RECTANGLEDRAWSYSTEM_H
