//
// Created by Arya Rakha on 6/26/2023.
//

#include <iostream>
#include "DestroyOnZeroHealthSystem.h"
#include "../components/Health.h"
#include "../components/debug/DebugName.h"
#include "../events/EntityDeathEvent.h"

void DestroyOnZeroHealthSystem::SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    registry->on_update<Health>().connect<&DestroyOnZeroHealthSystem::OnHealthUpdated>(this);
}

void DestroyOnZeroHealthSystem::UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {

}

void DestroyOnZeroHealthSystem::OnHealthUpdated(entt::registry &registry, entt::entity entity) {
    auto healthData = registry.try_get<Health>(entity);
    if (healthData == nullptr) throw std::invalid_argument("TRYING TO UPDATE HEALTH WITHOUT HEALTH DATA???");
}

void DestroyOnZeroHealthSystem::LateUpdate(entt::registry *registry) {
    auto view = registry->view<Health>();
    for (auto [entity, healthData] : view.each()) {
        if (healthData.health <= 0.f) {
            publisher->Publish(EntityDeathEvent{entity});
            registry->destroy(entity);
        }
    }
}
