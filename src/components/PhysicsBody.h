//
// Created by Arya Rakha on 6/6/2023.
//

#ifndef CMAKESFMLPROJECT_PHYSICSBODY_H
#define CMAKESFMLPROJECT_PHYSICSBODY_H

#include <box2d/box2d.h>
#include <memory>

class PhysicsBody {
public:
    b2Body* body;
    b2Fixture* fixture;
    b2Shape* shape;
};


#endif //CMAKESFMLPROJECT_PHYSICSBODY_H
