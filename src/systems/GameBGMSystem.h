//
// Created by Arya Rakha on 8/2/2023.
//

#ifndef ECSTEROID_GAMEBGMSYSTEM_H
#define ECSTEROID_GAMEBGMSYSTEM_H


#include "core/ILocateServicesSystem.h"
#include "core/ILoadableSystem.h"
#include "../services/SFMLAudioService.h"

class GameBGMSystem : public ILocateServicesSystem, public ILoadableSystem {
public:
    void LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) override;

    void Load(entt::registry *registry) override;

    void Unload() override;

private:
    std::shared_ptr<SFMLAudioService> audioService;
};


#endif //ECSTEROID_GAMEBGMSYSTEM_H
