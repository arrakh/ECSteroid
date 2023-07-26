//
// Created by Arya Rakha on 6/9/2023.
//

#ifndef CMAKESFMLPROJECT_APPLICATION_H
#define CMAKESFMLPROJECT_APPLICATION_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "scenes/GameScene.h"

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
};


#endif //CMAKESFMLPROJECT_APPLICATION_H
