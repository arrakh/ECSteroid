//
// Created by Arya Rakha on 9/23/2023.
//

#ifndef ECSTEROID_SFMLBUTTONSYSTEM_H
#define ECSTEROID_SFMLBUTTONSYSTEM_H


#include "../core/IUpdatableSystem.h"
#include "../core/IWindowInjectableSystem.h"
#include "../../application/SFMLWindow.h"
#include "../../components/Button.h"

class SFMLButtonSystem : public IUpdatableSystem, public IWindowInjectableSystem {
public:
    void Update(entt::registry *registry) override;
    void OnInject(std::shared_ptr<IWindow> window) override { sfWindow = std::dynamic_pointer_cast<SFMLWindow>(window);}

private:
    bool IsOverlappingButton(entt::registry *registry, entt::entity entity, Button& button, sf::View defaultView);
    void DetectButtonClick(entt::registry *registry, sf::View defaultView);
    void GenerateButtons(entt::registry *registry);

    entt::entity focusedButtonEntity { entt::null };
    std::shared_ptr<SFMLWindow> sfWindow;

};


#endif //ECSTEROID_SFMLBUTTONSYSTEM_H
