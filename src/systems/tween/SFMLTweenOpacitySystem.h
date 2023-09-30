//
// Created by Arya Rakha on 9/30/2023.
//

#ifndef ECSTEROID_SFMLTWEENOPACITYSYSTEM_H
#define ECSTEROID_SFMLTWEENOPACITYSYSTEM_H


#include "../core/IUpdatableSystem.h"

class SFMLTweenOpacitySystem : public IUpdatableSystem {
public:
    void Update(entt::registry *registry) override;

};


#endif //ECSTEROID_SFMLTWEENOPACITYSYSTEM_H
