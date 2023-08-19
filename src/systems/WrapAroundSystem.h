//
// Created by Arya Rakha on 6/12/2023.
//

#ifndef ECSTEROID_WRAPAROUNDSYSTEM_H
#define ECSTEROID_WRAPAROUNDSYSTEM_H


#include "core/IUpdatableSystem.h"
#include "core/IFixedUpdatableSystem.h"
#include "core/IWindowInjectableSystem.h"
#include "../application/SFMLWindow.h"

class WrapAroundSystem : public IUpdatableSystem, public IWindowInjectableSystem, public IFixedUpdatableSystem {
public:
    void Update(entt::registry *registry) override;

    void FixedUpdate(entt::registry *registry) override;

    void OnInject(std::shared_ptr<IWindow> window) override { sfWindow = std::dynamic_pointer_cast<SFMLWindow>(window);}

private:
    std::shared_ptr<SFMLWindow> sfWindow;
    Vector2 GetWrappedPosition(const Vector2 pos, const Vector2 topLeft, const Vector2 bottomRight);
};


#endif //ECSTEROID_WRAPAROUNDSYSTEM_H
