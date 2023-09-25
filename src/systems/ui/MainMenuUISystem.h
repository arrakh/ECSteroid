//
// Created by Arya Rakha on 9/24/2023.
//

#ifndef ECSTEROID_MAINMENUUISYSTEM_H
#define ECSTEROID_MAINMENUUISYSTEM_H

#include "../../datatype/Vector2.h"
#include "UISystem.h"
#include "../core/IUpdatableSystem.h"
#include "../core/IFinalUpdatableSystem.h"

class MainMenuUISystem : public UISystem, public IUpdatableSystem {
public:
protected:
public:
    void Update(entt::registry *registry) override;

protected:
    void OnLoad(entt::registry *registry) override;

    void OnUnload() override;

    sf::FloatRect GetViewport() override;

private:
    void CreateMainMenuButton(entt::registry *registry, Vector2 position, std::string text, std::function<void()> callback);
    void Quit();
    void Play();

    sf::View uiView;
};


#endif //ECSTEROID_MAINMENUUISYSTEM_H
