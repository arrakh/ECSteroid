//
// Created by Arya Rakha on 6/4/2023.
//

#ifndef CMAKESFMLPROJECT_TIME_H
#define CMAKESFMLPROJECT_TIME_H

#include <SFML/Graphics.hpp>

class Time {
public:
    static float deltaTime();
    static sf::Time deltaSFTime();
    static float fixedDeltaTime();
    static void updateDeltaTime();

private:
    static float dt;
    static float fixedDtRate;
    static sf::Time sfDt;
    static sf::Clock deltaClock;
};


#endif //CMAKESFMLPROJECT_TIME_H
