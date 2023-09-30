//
// Created by Arya Rakha on 9/27/2023.
//

#ifndef ECSTEROID_TWEENLOCALPOSITIONSYSTEM_H
#define ECSTEROID_TWEENLOCALPOSITIONSYSTEM_H


#include "../core/IUpdatableSystem.h"
#include "../../datatype/Ease.h"

class TweenLocalPositionSystem : public IUpdatableSystem {
public:
    void Update(entt::registry *registry) override;

};


#endif //ECSTEROID_TWEENLOCALPOSITIONSYSTEM_H
