//
// Created by Arya Rakha on 9/27/2023.
//

#include "TweenSystems.h"
#include "TweenTimerSystem.h"
#include "TweenLocalPositionSystem.h"
#include "TweenWorldPositionSystem.h"

void Tween::RegisterSystems(SystemsHandler *handle) {
    handle->Register(new TweenTimerSystem());
    handle->Register(new TweenLocalPositionSystem());
    handle->Register(new TweenWorldPositionSystem());
}
