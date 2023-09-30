//
// Created by Arya Rakha on 9/30/2023.
//

#ifndef ECSTEROID_TWEENWORLDPOSITIONSYSTEM_H
#define ECSTEROID_TWEENWORLDPOSITIONSYSTEM_H


#include "../core/IUpdatableSystem.h"

class TweenWorldPositionSystem : public IUpdatableSystem {
public:
    void Update(entt::registry *registry) override;

};


#endif //ECSTEROID_TWEENWORLDPOSITIONSYSTEM_H
