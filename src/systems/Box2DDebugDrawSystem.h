//
// Created by Arya Rakha on 6/11/2023.
//

#ifndef CMAKESFMLPROJECT_BOX2DDEBUGDRAWSYSTEM_H
#define CMAKESFMLPROJECT_BOX2DDEBUGDRAWSYSTEM_H

#include "core/IRenderableSystem.h"
#include "../components/debug/Box2DDebug.h"
#include "../components/PhysicsBody.h"
#include "core/IFixedUpdatableSystem.h"

class Box2DDebugDrawSystem : public IRenderableSystem, public IFixedUpdatableSystem {
public:
    void Render(entt::registry *registry, sf::RenderTarget *renderTarget) override;

private:
    void FixedUpdate(entt::registry *registry) override;

public:
    int GetRenderOrder() override;
};


#endif //CMAKESFMLPROJECT_BOX2DDEBUGDRAWSYSTEM_H
