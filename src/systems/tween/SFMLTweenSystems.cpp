//
// Created by Arya Rakha on 9/30/2023.
//

#include "SFMLTweenSystems.h"
#include "SFMLTweenScaleSystem.h"
#include "SFMLTweenOpacitySystem.h"

void Tween::RegisterSFMLSystems(SystemsHandler *handle) {
    handle->Register(new SFMLTweenOpacitySystem());
    handle->Register(new SFMLTweenScaleSystem());
}

