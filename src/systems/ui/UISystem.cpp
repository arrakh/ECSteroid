//
// Created by Arya Rakha on 9/24/2023.
//

#include <cfloat>
#include <iostream>
#include "UISystem.h"

void UISystem::Load(entt::registry *registry) {
    OnLoad(registry);
}

void UISystem::Unload() {
    OnUnload();
}
