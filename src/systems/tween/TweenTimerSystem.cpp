//
// Created by Arya Rakha on 9/27/2023.
//

#include "TweenTimerSystem.h"
#include "../../components/tween/TweenTimer.h"
#include "../../util/Time.h"

void TweenTimerSystem::Update(entt::registry *registry) {
    auto timers = registry->view<TweenTimer>();
    for (auto [entity, timer] : timers.each()) {
        timer.currentTime += Time::deltaTime();
    }
}

void TweenTimerSystem::FinalUpdate(entt::registry *registry) {
    auto timers = registry->view<TweenTimer>();
    for (auto [entity, timer] : timers.each()) {
        if (timer.currentTime < timer.totalTime) continue;
        registry->destroy(entity);
    }
}
