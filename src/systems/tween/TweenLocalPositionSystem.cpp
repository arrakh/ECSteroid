//
// Created by Arya Rakha on 9/27/2023.
//

#include <iostream>
#include "TweenLocalPositionSystem.h"
#include "../../components/tween/TweenTimer.h"
#include "../../components/tween/TweenLocalPosition.h"
#include "../../components/LocalPosition.h"
#include "../../components/tween/TweenEase.h"
#include "../../components/debug/DebugName.h"
#include "../../components/tween/TweenTarget.h"

void TweenLocalPositionSystem::Update(entt::registry *registry) {
    auto tweens = registry->view<TweenTimer, TweenTarget, TweenLocalPosition>();
    for (auto [entity, timer, target, tween] : tweens.each()) {
        auto alpha = timer.GetProgress();

        auto ease = TweenEase::GetType(registry, entity);
        float finalX = Ease::Calculate(ease, tween.from.x, tween.to.x, alpha);
        float finalY = Ease::Calculate(ease, tween.from.y, tween.to.y, alpha);

        //std::cout << DebugName::Get(registry, target.entity) << ": A:" << alpha << ", X:" << finalX << ", Y:" << finalY << "\n";

        registry->emplace_or_replace<LocalPosition>(target.entity, LocalPosition{Vector2 { finalX, finalY }});
    }
}
