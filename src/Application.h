//
// Created by Arya Rakha on 6/9/2023.
//

#ifndef CMAKESFMLPROJECT_APPLICATION_H
#define CMAKESFMLPROJECT_APPLICATION_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "scenes/GameScene.h"
#include "services/core/ServicesHandler.h"
#include "services/core/ServiceLocator.h"

class Application {
public:
    void Run();

    float fixedTickAccumulator = 0;

    static float Width;
    static float Height;
    static unsigned int Width_u;
    static unsigned int Height_u;
    static std::shared_ptr<sf::RenderWindow> WindowPtr;

    void GameLoop(Scene *currentScene);

private:
    ServicesHandler servicesHandler;
    std::shared_ptr<ServiceLocator> serviceLocator;

    void RegisterServices();
};


#endif //CMAKESFMLPROJECT_APPLICATION_H
