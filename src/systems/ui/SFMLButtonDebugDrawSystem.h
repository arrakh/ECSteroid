//
// Created by Arya Rakha on 9/24/2023.
//

#ifndef ECSTEROID_SFMLBUTTONDEBUGDRAWSYSTEM_H
#define ECSTEROID_SFMLBUTTONDEBUGDRAWSYSTEM_H


#include "../core/IRenderableSystem.h"
#include "../core/IWindowInjectableSystem.h"
#include "../../application/SFMLWindow.h"

class SFMLButtonDebugDrawSystem : public IRenderableSystem, public IWindowInjectableSystem {
    void Render(entt::registry *registry) override;

    int GetRenderOrder() override;

    void OnInject(std::shared_ptr<IWindow> window) override { sfWindow = std::dynamic_pointer_cast<SFMLWindow>(window);}

private:
    std::shared_ptr<SFMLWindow> sfWindow;
};


#endif //ECSTEROID_SFMLBUTTONDEBUGDRAWSYSTEM_H
