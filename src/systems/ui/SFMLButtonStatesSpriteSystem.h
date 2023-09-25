//
// Created by Arya Rakha on 9/24/2023.
//

#ifndef ECSTEROID_SFMLBUTTONSTATESSPRITESYSTEM_H
#define ECSTEROID_SFMLBUTTONSTATESSPRITESYSTEM_H


#include "../core/ILateUpdatableSystem.h"
#include "../core/ILocateServicesSystem.h"
#include "../../services/SFMLTextureService.h"

class SFMLButtonStatesSpriteSystem : public ILateUpdatableSystem, public ILocateServicesSystem {
public:
    void LateUpdate(entt::registry *registry) override;

    void LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) override;

private:
    std::shared_ptr<SFMLTextureService> textureService;

};


#endif //ECSTEROID_SFMLBUTTONSTATESSPRITESYSTEM_H
