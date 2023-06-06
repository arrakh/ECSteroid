//
// Created by Arya Rakha on 6/6/2023.
//

#ifndef CMAKESFMLPROJECT_PHYSICSDEFINITION_H
#define CMAKESFMLPROJECT_PHYSICSDEFINITION_H

#include <box2d/box2d.h>

class PhysicsDefinition {
public:
    b2BodyDef const bodyDef;
    b2FixtureDef const fixtureDef;
};


#endif //CMAKESFMLPROJECT_PHYSICSDEFINITION_H
