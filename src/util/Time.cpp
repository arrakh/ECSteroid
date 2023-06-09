//
// Created by Arya Rakha on 6/4/2023.
//

#include "Time.h"

float Time::deltaTime() {
    return dt;
}

float Time::fixedDeltaTime() {
    return 1.f / fixedDtRate;
}

void Time::updateDeltaTime() {
    sfDt = deltaClock.restart();
    dt = sfDt.asSeconds();
}

sf::Time Time::sfDt;
float Time::dt = 0;
float Time::fixedDtRate = 60.f;

sf::Time Time::deltaSFTime() {
    return sfDt;
}

sf::Clock Time::deltaClock;
