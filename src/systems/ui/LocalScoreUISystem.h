//
// Created by Arya Rakha on 7/25/2023.
//

#ifndef ECSTEROID_LOCALSCOREUISYSTEM_H
#define ECSTEROID_LOCALSCOREUISYSTEM_H


#include "../core/IRenderableSystem.h"
#include "../core/ILoadableSystem.h"
#include "../../datatype/Vector2.h"

class LocalScoreUISystem : public IRenderableSystem, public ILoadableSystem {
public:
    void Render(entt::registry *registry, sf::RenderTarget *renderTarget) override;

    int GetRenderOrder() override;

    void Load(entt::registry *registry) override;

    void Unload() override;

private:
    sf::Text text;
    sf::Font font;
    sf::View uiView;
    Vector2 offset {30.f, 20.f };

    int GetAnimatedScore(const entt::registry *registry) const;
    int GetTargetScore(const entt::registry *registry) const;
};


#endif //ECSTEROID_LOCALSCOREUISYSTEM_H
