//
// Created by Arya Rakha on 9/24/2023.
//

#ifndef ECSTEROID_UISYSTEM_H
#define ECSTEROID_UISYSTEM_H


#include "../core/IWindowInjectableSystem.h"
#include "../core/ILoadableSystem.h"
#include "SFML/Graphics.hpp"
#include "../../application/SFMLWindow.h"
#include "../core/IRenderableSystem.h"
#include "../core/IFinalUpdatableSystem.h"

class UISystem : public IWindowInjectableSystem, public ILoadableSystem {
protected:
    virtual void OnLoad(entt::registry *registry) = 0;
    virtual void OnUnload() = 0;
    virtual sf::FloatRect GetViewport() = 0;

    sf::View uiView{};
    std::shared_ptr<SFMLWindow> sfWindow;

public:
    void Load(entt::registry *registry) override;
    void Unload() override;

    void OnInject(std::shared_ptr<IWindow> window) override { sfWindow = std::dynamic_pointer_cast<SFMLWindow>(window);}
};


#endif //ECSTEROID_UISYSTEM_H
