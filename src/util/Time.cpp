//
// Created by Arya Rakha on 6/4/2023.
//

#include "Time.h"

float Time::deltaTime() {
    return dt;
}

void Time::updateDeltaTime() {
    dt = deltaClock.restart().asSeconds();
}

float Time::dt = 0;
sf::Clock Time::deltaClock;
