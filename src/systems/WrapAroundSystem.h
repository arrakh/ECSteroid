//
// Created by Arya Rakha on 6/12/2023.
//

#ifndef ECSTEROID_WRAPAROUNDSYSTEM_H
#define ECSTEROID_WRAPAROUNDSYSTEM_H


#include "core/IUpdatableSystem.h"
#include "core/IFixedUpdatableSystem.h"

class WrapAroundSystem : public IUpdatableSystem, public IFixedUpdatableSystem {
public:
    void Update(entt::registry *registry) override;

    void FixedUpdate(entt::registry *registry) override;

private:
    Vector2 GetWrappedPosition(const Vector2 pos, const Vector2 topLeft, const Vector2 bottomRight);
};


#endif //ECSTEROID_WRAPAROUNDSYSTEM_H
