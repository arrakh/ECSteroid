//
// Created by Arya Rakha on 6/5/2023.
//

#include "SystemsHandler.h"

void SystemsHandler::UpdateSystems(entt::registry* registry) {
    for (const auto& system : updatables) {
        system->Update(registry);
    }
}

void SystemsHandler::RenderSystems(entt::registry* registry, sf::RenderTarget* renderTarget) {
    for (const auto& system : renderables) {
        system->Render(registry, renderTarget);
    }
}

void SystemsHandler::LoadSystems(entt::registry* registry) {
    for (const auto& system : loadables) {
        system->Load(registry);
    }
}

void SystemsHandler::UnloadSystems() {
    for (const auto& system : loadables) {
        system->Unload();
    }
}

void SystemsHandler::FixedUpdateSystems(entt::registry *registry) {
    for (const auto& system : fixedUpdatables) {
        system->FixedUpdate(registry);
    }
}

void SystemsHandler::RegisterEvents(entt::registry *registry, Events::Subscriber* listener) {
    for (const auto& system : eventRegistrables) {
        system->SubscribeEvents(registry, listener);
    }
}

void SystemsHandler::UnregisterEvents(entt::registry *registry, Events::Subscriber* listener) {
    for (const auto& system : eventRegistrables) {
        system->UnsubscribeEvents(registry, listener);
    }
}

void SystemsHandler::SortRenderables() {
    std::sort(renderables.begin(), renderables.end(), [](const auto& a, const auto& b) {
        return a->GetRenderOrder() < b->GetRenderOrder();
    });
}

void SystemsHandler::InjectPublisher(Events::Publisher *publisher) {
    for (const auto& system : eventPublishers) {
        system->OnInjectPublisher(publisher);
    }
}
