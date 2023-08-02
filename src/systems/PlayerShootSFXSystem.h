//
// Created by Arya Rakha on 8/2/2023.
//

#ifndef ECSTEROID_PLAYERSHOOTSFXSYSTEM_H
#define ECSTEROID_PLAYERSHOOTSFXSYSTEM_H


#include "core/IEventSubscriberSystem.h"
#include "core/ILocateServicesSystem.h"
#include "../services/SFMLAudioService.h"

class PlayerShootSFXSystem : public ILocateServicesSystem, public IEventSubscriberSystem {
public:
    void SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) override;

private:
    std::shared_ptr<SFMLAudioService> audioService;

    void OnBulletSpawned(entt::registry & registry, entt::entity entity);
};


#endif //ECSTEROID_PLAYERSHOOTSFXSYSTEM_H
