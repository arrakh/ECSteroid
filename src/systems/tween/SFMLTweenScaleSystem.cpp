//
// Created by Arya Rakha on 9/30/2023.
//

#include <iostream>
#include "SFMLTweenScaleSystem.h"
#include "../../components/tween/TweenTarget.h"
#include "../../components/tween/TweenTimer.h"
#include "../../components/tween/TweenScale.h"
#include "../../components/tween/TweenEase.h"
#include "../../components/SFMLTransformable.h"

void SFMLTweenScaleSystem::Update(entt::registry *registry) {
    auto tweens = registry->view<TweenTarget, TweenTimer, TweenScale>();

    for (auto [entity, target, timer, tween] : tweens.each()) {
        auto transformable = registry->try_get<SFMLTransformable>(target.entity);
        if (transformable == nullptr) continue;

        auto ease = TweenEase::GetType(registry, entity);
        auto alpha = timer.GetProgress();
        float scaleX = Ease::Calculate(ease, tween.from.x, tween.to.x, alpha);
        float scaleY = Ease::Calculate(ease, tween.from.y, tween.to.y, alpha);

        transformable->transformable->setScale(scaleX, scaleY);
    }
}
