//
// Created by Arya Rakha on 9/27/2023.
//

#ifndef ECSTEROID_TWEENTIMERSYSTEM_H
#define ECSTEROID_TWEENTIMERSYSTEM_H


#include "../core/IUpdatableSystem.h"
#include "../core/IFinalUpdatableSystem.h"

class TweenTimerSystem : public IUpdatableSystem, public IFinalUpdatableSystem {
public:
    void Update(entt::registry *registry) override;

    void FinalUpdate(entt::registry *registry) override;

};


#endif //ECSTEROID_TWEENTIMERSYSTEM_H
