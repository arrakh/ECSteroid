//
// Created by Arya Rakha on 10/8/2023.
//

#ifndef ECSTEROID_MAINMENUUIBACKGROUNDSYSTEM_H
#define ECSTEROID_MAINMENUUIBACKGROUNDSYSTEM_H

#include "../core/ILoadableSystem.h"
#include "../core/IUpdatableSystem.h"
#include "UISystem.h"

class MainMenuUIBackgroundSystem : public UISystem , public IUpdatableSystem {
public:

    void Update(entt::registry *registry) override;

protected:
    void OnLoad(entt::registry *registry) override;

    void OnUnload() override;

    sf::FloatRect GetViewport() override;

};


#endif //ECSTEROID_MAINMENUUIBACKGROUNDSYSTEM_H
