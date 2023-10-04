//
// Created by Arya Rakha on 9/30/2023.
//

#include <iostream>
#include "SFMLTweenScaleSystem.h"
#include "../../components/tween/TweenScale.h"
#include "../../components/SFMLTransformable.h"
#include "../../components/SFMLSprite.h"
#include "../../components/tween/TweenData.h"

void SFMLTweenScaleSystem::Update(entt::registry *registry) {
    auto tweens = registry->view<TweenData, TweenScale>();

    for (auto [entity, data, tween] : tweens.each()) {
        auto transformable = registry->try_get<SFMLTransformable>(data.target);
        if (transformable == nullptr) continue;

        auto alpha = data.GetProgress();
        float scaleX = Ease::Calculate(data.ease, tween.from.x, tween.to.x, alpha);
        float scaleY = Ease::Calculate(data.ease, tween.from.y, tween.to.y, alpha);

        auto sprite = registry->try_get<SFMLSprite>(data.target);
        if (sprite != nullptr){
            scaleX = scaleX * sprite->spriteScale.x;
            scaleY = scaleY * sprite->spriteScale.y;
        }

        transformable->transformable->setScale(scaleX, scaleY);
    }
}
