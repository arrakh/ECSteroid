//
// Created by Arya Rakha on 9/30/2023.
//

#include <iostream>
#include "TweenWorldPositionSystem.h"
#include "../../components/tween/TweenTimer.h"
#include "../../components/tween/TweenEase.h"
#include "../../components/WorldPosition.h"
#include "../../components/tween/TweenTarget.h"
#include "../../components/tween/TweenWorldPosition.h"
#include "../../components/debug/DebugName.h"

void TweenWorldPositionSystem::Update(entt::registry *registry) {
    auto tweens = registry->view<TweenTimer, TweenTarget, TweenWorldPosition>();
    for (auto [entity, timer, target, tween] : tweens.each()) {
        auto alpha = timer.GetProgress();

        auto ease = TweenEase::GetType(registry, entity);
        float finalX = Ease::Calculate(ease, tween.from.x, tween.to.x, alpha);
        float finalY = Ease::Calculate(ease, tween.from.y, tween.to.y, alpha);

        registry->emplace_or_replace<WorldPosition>(target.entity, WorldPosition{Vector2 { finalX, finalY }});
    }
}
