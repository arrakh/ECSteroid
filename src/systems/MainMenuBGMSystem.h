//
// Created by Arya Rakha on 10/8/2023.
//

#ifndef ECSTEROID_MAINMENUBGMSYSTEM_H
#define ECSTEROID_MAINMENUBGMSYSTEM_H


#include "core/ILocateServicesSystem.h"

class MainMenuBGMSystem : public ILocateServicesSystem {
public:
    void LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) override;

};


#endif //ECSTEROID_MAINMENUBGMSYSTEM_H
