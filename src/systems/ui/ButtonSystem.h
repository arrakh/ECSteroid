//
// Created by Arya Rakha on 9/23/2023.
//

#ifndef ECSTEROID_BUTTONSYSTEM_H
#define ECSTEROID_BUTTONSYSTEM_H


#include "../core/ILateUpdatableSystem.h"

class ButtonSystem : public ILateUpdatableSystem{
public:
    void LateUpdate(entt::registry *registry) override;

private:
    entt::entity focusedButtonEntity = entt::null;

};


#endif //ECSTEROID_BUTTONSYSTEM_H
