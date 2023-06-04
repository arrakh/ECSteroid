//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_TIME_H
#define CMAKESFMLPROJECT_TIME_H

#include <SFML/Graphics.hpp>

class Time {
public:
    static float deltaTime();
    static void updateDeltaTime();

private:
    static float dt;
    static sf::Clock deltaClock;
};


#endif //CMAKESFMLPROJECT_TIME_H
