//
// Created by Arya Rakha on 9/30/2023.
//

#ifndef ECSTEROID_SFMLTWEENSCALESYSTEM_H
#define ECSTEROID_SFMLTWEENSCALESYSTEM_H


#include "../core/IUpdatableSystem.h"

class SFMLTweenScaleSystem : public IUpdatableSystem {
public:
    void Update(entt::registry *registry) override;
};


#endif //ECSTEROID_SFMLTWEENSCALESYSTEM_H
