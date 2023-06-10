//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_SFMLRENDERSYSTEM_H
#define CMAKESFMLPROJECT_SFMLRENDERSYSTEM_H

#include "core/IRenderableSystem.h"
#include "../events/TestEvent.h"
#include "core/ILoadableSystem.h"

class SFMLRenderSystem : public IRenderableSystem, public ILoadableSystem {
public:
    void Render(entt::registry* registry, sf::RenderTarget* renderTarget) override;

    int GetRenderOrder() override;

    void Load(entt::registry *registry) override;

    void Unload() override;

    void ApplyTransforms(entt::registry *pRegistry);

    void RenderDrawables(entt::registry *pRegistry, sf::RenderTarget *pTarget);
};


#endif //CMAKESFMLPROJECT_SFMLRENDERSYSTEM_H
