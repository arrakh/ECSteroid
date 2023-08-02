//
// Created by Arya Rakha on 8/2/2023.
//

#ifndef ECSTEROID_GAMEBGMSYSTEM_H
#define ECSTEROID_GAMEBGMSYSTEM_H


#include "core/ILocateServicesSystem.h"

class GameBGMSystem : public ILocateServicesSystem {
public:
    void LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) override;

};


#endif //ECSTEROID_GAMEBGMSYSTEM_H
