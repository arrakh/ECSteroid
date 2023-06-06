//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_IRENDERABLESYSTEM_H
#define CMAKESFMLPROJECT_IRENDERABLESYSTEM_H


#include "SFML/Graphics.hpp"
#include "entt/entt.hpp"

class IRenderableSystem {
public:
    virtual void Render(entt::registry* registry, sf::RenderTarget* renderTarget) = 0;
    virtual int GetRenderOrder() = 0;
};


#endif //CMAKESFMLPROJECT_IRENDERABLESYSTEM_H
