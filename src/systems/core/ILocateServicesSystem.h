//
// Created by Arya Rakha on 7/27/2023.
//

#ifndef ECSTEROID_ILOCATESERVICESSYSTEM_H
#define ECSTEROID_ILOCATESERVICESSYSTEM_H


#include <memory>
#include "../../services/core/ServiceLocator.h"

class ILocateServicesSystem {
public:
    virtual void LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) = 0;
};


#endif //ECSTEROID_ILOCATESERVICESSYSTEM_H
