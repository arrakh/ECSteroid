//
// Created by Arya Rakha on 9/27/2023.
//

#include <iostream>
#include "TweenLocalPositionSystem.h"
#include "../../components/tween/TweenLocalPosition.h"
#include "../../components/LocalPosition.h"
#include "../../components/debug/DebugName.h"
#include "../../components/tween/TweenData.h"

void TweenLocalPositionSystem::Update(entt::registry *registry) {
    auto tweens = registry->view<TweenData, TweenLocalPosition>();
    for (auto [entity, data, tween] : tweens.each()) {
        auto alpha = data.GetProgress();

        float finalX = Ease::Calculate(data.ease, tween.from.x, tween.to.x, alpha);
        float finalY = Ease::Calculate(data.ease, tween.from.y, tween.to.y, alpha);

        //std::cout << DebugName::Get(registry, target.entity) << ": A:" << alpha << ", X:" << finalX << ", Y:" << finalY << "\n";

        registry->emplace_or_replace<LocalPosition>(data.target, LocalPosition{Vector2 { finalX, finalY }});
    }
}
