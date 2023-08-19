//
// Created by Arya Rakha on 8/2/2023.
//

#ifndef ECSTEROID_ECSTEROIDAPPLICATION_H
#define ECSTEROID_ECSTEROIDAPPLICATION_H


#include "Application.h"

class ECSteroidApplication : public Application {
protected:
    std::unique_ptr<Scene> GetInitialScene() override;

    void RegisterServices() override;

    IWindow* GetWindow() override;
};


#endif //ECSTEROID_ECSTEROIDAPPLICATION_H
