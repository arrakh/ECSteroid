//
// Created by Arya Rakha on 6/4/2023.
//

#include "Time.h"

float Time::deltaTime() {
    return dt;
}

float Time::fixedDeltaTime() {
    return 1 / fixedDtRate;
}

void Time::updateDeltaTime() {
    dt = deltaClock.restart().asSeconds();
}

float Time::dt = 0;
float Time::fixedDtRate = 60.f;
sf::Clock Time::deltaClock;
