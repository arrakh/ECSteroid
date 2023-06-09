//
// Created by Arya Rakha on 6/8/2023.
//

#ifndef CMAKESFMLPROJECT_TESTEVENT_H
#define CMAKESFMLPROJECT_TESTEVENT_H

#include "../systems/core/EventSystem.h"

struct TestEvent : public Event {
    TestEvent() {}

    TestEvent(int value, float fValue) : value(value), fValue(fValue) {}

    int value;
    float fValue;
};

#endif //CMAKESFMLPROJECT_TESTEVENT_H
