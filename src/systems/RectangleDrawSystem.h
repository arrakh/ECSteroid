//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_RECTANGLEDRAWSYSTEM_H
#define CMAKESFMLPROJECT_RECTANGLEDRAWSYSTEM_H

#include "IRenderableSystem.h"

class RectangleDrawSystem : public IRenderableSystem{
public:
    void Render(entt::registry* registry, sf::RenderTarget* renderTarget) override;

    int GetRenderOrder() override;
};


#endif //CMAKESFMLPROJECT_RECTANGLEDRAWSYSTEM_H
