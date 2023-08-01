//
// Created by Arya Rakha on 7/9/2023.
//

#ifndef ECSTEROID_GAMEOVERTEXTUISYSTEM_H
#define ECSTEROID_GAMEOVERTEXTUISYSTEM_H

#include "SFML/Graphics.hpp"
#include "../core/ILoadableSystem.h"
#include "../core/IRenderableSystem.h"
#include "../core/IEventSubscriberSystem.h"
#include "../../services/SFMLFontService.h"
#include "../core/ILocateServicesSystem.h"

class GameOverTextUISystem : public IRenderableSystem, public ILoadableSystem, public IEventSubscriberSystem, public ILocateServicesSystem {
    void Load(entt::registry *registry) override;

    void Unload() override;

    void Render(entt::registry *registry, sf::RenderTarget *renderTarget) override;

    int GetRenderOrder() override;

    void SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

    void UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) override;

private:
    sf::RectangleShape blackBg;
    sf::Text gameOverText;
    sf::View uiView;
    std::shared_ptr<SFMLFontService> fontService;

    bool isGameOver = false;
    float alphaProgress = 0;
    float animateDuration = 3.f;

    void OnLocalPlayerDestroyed();

public:
    void LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) override;
};


#endif //ECSTEROID_GAMEOVERTEXTUISYSTEM_H
