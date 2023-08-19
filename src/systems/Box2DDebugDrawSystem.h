//
// Created by Arya Rakha on 6/11/2023.
//

#ifndef CMAKESFMLPROJECT_BOX2DDEBUGDRAWSYSTEM_H
#define CMAKESFMLPROJECT_BOX2DDEBUGDRAWSYSTEM_H

#include "core/IRenderableSystem.h"
#include "../components/debug/Box2DDebug.h"
#include "../components/PhysicsBody.h"
#include "core/IFixedUpdatableSystem.h"
#include "core/IUpdatableSystem.h"
#include "core/IWindowInjectableSystem.h"
#include "../application/SFMLWindow.h"

class Box2DDebugDrawSystem : public IRenderableSystem, public IWindowInjectableSystem, public IFixedUpdatableSystem, public IUpdatableSystem {
public:
    void Render(entt::registry *registry) override;
    int GetRenderOrder() override;

    void Update(entt::registry *registry) override;

    void OnInject(std::shared_ptr<IWindow> window) override {sfWindow = std::dynamic_pointer_cast<SFMLWindow>(window);}

private:
    std::shared_ptr<SFMLWindow> sfWindow;
    void FixedUpdate(entt::registry *registry) override;
    static bool shouldDraw;
};


#endif //CMAKESFMLPROJECT_BOX2DDEBUGDRAWSYSTEM_H
