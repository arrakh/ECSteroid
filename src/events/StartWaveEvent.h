//
// Created by Arya Rakha on 8/12/2023.
//

#ifndef ECSTEROID_STARTWAVEEVENT_H
#define ECSTEROID_STARTWAVEEVENT_H


#include "../systems/core/EventSystem.h"
#include "../datatype/CreateAsteroidParameter.h"

class StartWaveEvent : public Event {
public:
    int waveNumber;
    std::vector<CreateAsteroidParameter> params;
};


#endif //ECSTEROID_STARTWAVEEVENT_H
