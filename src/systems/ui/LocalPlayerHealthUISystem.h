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
#include "../../application/Application.h"

class LocalPlayerHealthUISystem : public IRenderableSystem, public IWindowInjectableSystem, public ILoadableSystem {
public:
    void Load(entt::registry *registry) override;

    void Render(entt::registry *registry) override;

    int GetRenderOrder() override;

    void Unload() override;

    void OnInject(std::shared_ptr<IWindow> window) override { sfWindow = std::dynamic_pointer_cast<SFMLWindow>(window);}

private:
    std::shared_ptr<SFMLWindow> sfWindow;

    sf::RectangleShape healthBgBar;
    sf::RectangleShape healthBar;
    Vector2 barSize { 500, 30 };
    Vector2 barOffset {30, 30 };
    sf::View uiView;
};


#endif //ECSTEROID_LOCALPLAYERHEALTHUISYSTEM_H
