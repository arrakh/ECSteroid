//
// Created by Arya Rakha on 7/8/2023.
//

#ifndef ECSTEROID_LOCALPLAYERHEALTHUISYSTEM_H
#define ECSTEROID_LOCALPLAYERHEALTHUISYSTEM_H

#include "SFML/Graphics.hpp"
#include "../core/IUpdatableSystem.h"
#include "../../datatype/Vector2.h"
#include "../core/ILoadableSystem.h"
#include "../core/IRenderableSystem.h"
#include "../../Application.h"

class LocalPlayerHealthUISystem : public IRenderableSystem, public ILoadableSystem {
public:
    void Load(entt::registry *registry) override;

    void Render(entt::registry *registry, sf::RenderTarget *renderTarget) override;

    int GetRenderOrder() override;

    void Unload() override;

private:
    sf::RectangleShape healthBgBar;
    sf::RectangleShape healthBar;
    Vector2 barSize { 200, 40 };
    Vector2 barOffset {30, 30 };
    sf::View uiView;
};


#endif //ECSTEROID_LOCALPLAYERHEALTHUISYSTEM_H
