//
// Created by Arya Rakha on 6/11/2023.
//

#ifndef CMAKESFMLPROJECT_SFMLSPRITESYSTEM_H
#define CMAKESFMLPROJECT_SFMLSPRITESYSTEM_H


#include "core/ILoadableSystem.h"
#include "core/IUpdatableSystem.h"
#include "../services/SFMLTextureService.h"
#include "core/ILocateServicesSystem.h"
#include <SFML/Graphics.hpp>

class SFMLSpriteSystem : public ILocateServicesSystem, public IUpdatableSystem  {
public:

    void Update(entt::registry *registry) override;

    void LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) override;

private:
    std::shared_ptr<SFMLTextureService> textureService;

};


#endif //CMAKESFMLPROJECT_SFMLSPRITESYSTEM_H
