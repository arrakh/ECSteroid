//
// Created by Arya Rakha on 9/27/2023.
//

#include <iostream>
#include "TweenTimerSystem.h"
#include "../../util/Time.h"
#include "../../components/tween/TweenData.h"

void TweenTimerSystem::Update(entt::registry *registry) {
    auto timers = registry->view<TweenData>();
    for (auto [entity, timer] : timers.each()) {
        timer.currentTime += Time::deltaTime();
    }
}

void TweenTimerSystem::FinalUpdate(entt::registry *registry) {
    auto timers = registry->view<TweenData>();
    for (auto [entity, timer] : timers.each()) {
        if (timer.currentTime < timer.totalTime) continue;
        registry->destroy(entity);
    }
}
