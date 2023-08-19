//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_SFMLRENDERSYSTEM_H
#define CMAKESFMLPROJECT_SFMLRENDERSYSTEM_H

#include "core/IRenderableSystem.h"
#include "../events/TestEvent.h"
#include "core/ILoadableSystem.h"
#include "core/IWindowInjectableSystem.h"
#include "../application/SFMLWindow.h"

class SFMLRenderSystem : public IRenderableSystem, public IWindowInjectableSystem, public ILoadableSystem {
public:
    void Render(entt::registry* registry) override;

    int GetRenderOrder() override;

    void OnInject(std::shared_ptr<IWindow> window) override { sfWindow = std::dynamic_pointer_cast<SFMLWindow>(window); }

    void Load(entt::registry *registry) override;

    void Unload() override;

    void ApplyTransforms(entt::registry *pRegistry);

    void RenderDrawables(entt::registry *pRegistry);

private:
    std::shared_ptr<SFMLWindow> sfWindow;
};


#endif //CMAKESFMLPROJECT_SFMLRENDERSYSTEM_H
