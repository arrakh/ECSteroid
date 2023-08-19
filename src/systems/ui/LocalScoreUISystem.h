//
// Created by Arya Rakha on 7/25/2023.
//

#ifndef ECSTEROID_LOCALSCOREUISYSTEM_H
#define ECSTEROID_LOCALSCOREUISYSTEM_H


#include "../core/IRenderableSystem.h"
#include "../core/ILoadableSystem.h"
#include "../../datatype/Vector2.h"
#include "../../services/SFMLFontService.h"
#include "../core/ILocateServicesSystem.h"
#include "../core/IWindowInjectableSystem.h"
#include "../../application/SFMLWindow.h"

class LocalScoreUISystem : public IRenderableSystem, public IWindowInjectableSystem, public ILoadableSystem, public ILocateServicesSystem {
public:
    void Render(entt::registry *registry) override;

    int GetRenderOrder() override;

    void Load(entt::registry *registry) override;

    void Unload() override;

    void LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) override;

    void OnInject(std::shared_ptr<IWindow> window) override { sfWindow = std::dynamic_pointer_cast<SFMLWindow>(window);}

private:
    std::shared_ptr<SFMLWindow> sfWindow;
    sf::Text text;
    std::shared_ptr<sf::Font> gameOverFont;
    std::shared_ptr<SFMLFontService> fontService;

    sf::View uiView;
    Vector2 offset {30.f, 20.f };

    int GetAnimatedScore(const entt::registry *registry) const;
    int GetTargetScore(const entt::registry *registry) const;
};


#endif //ECSTEROID_LOCALSCOREUISYSTEM_H
