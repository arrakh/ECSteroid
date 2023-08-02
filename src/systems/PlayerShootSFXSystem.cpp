//
// Created by Arya Rakha on 8/2/2023.
//

#include "PlayerShootSFXSystem.h"
#include "../components/bullet/BulletOwner.h"
#include "../components/LocalPlayer.h"
#include "../util/Random.h"

void PlayerShootSFXSystem::SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    registry->on_construct<BulletOwner>().connect<&PlayerShootSFXSystem::OnBulletSpawned>(this);
}

void PlayerShootSFXSystem::UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    registry->on_construct<BulletOwner>().disconnect<&PlayerShootSFXSystem::OnBulletSpawned>(this);
}

void PlayerShootSFXSystem::LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) {
    audioService = serviceLocator->Locate<SFMLAudioService>();
}

void PlayerShootSFXSystem::OnBulletSpawned(entt::registry &registry, entt::entity entity) {
    auto ownerData = registry.get<BulletOwner>(entity);

    if (!registry.any_of<LocalPlayer>(ownerData.entity)) return;

    audioService->PlaySFX("laser", {30.f, Random::Range(0.8f, 1.2f)});
}
