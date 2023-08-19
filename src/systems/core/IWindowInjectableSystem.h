//
// Created by Arya Rakha on 8/19/2023.
//

#ifndef ECSTEROID_IWINDOWINJECTABLESYSTEM_H
#define ECSTEROID_IWINDOWINJECTABLESYSTEM_H


#include "../../application/IWindow.h"

class IWindowInjectableSystem {
public:
    virtual void OnInject(std::shared_ptr<IWindow> window) = 0;
};


#endif //ECSTEROID_IWINDOWINJECTABLESYSTEM_H
