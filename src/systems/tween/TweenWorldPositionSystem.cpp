//
// Created by Arya Rakha on 9/30/2023.
//

#include <iostream>
#include "TweenWorldPositionSystem.h"
#include "../../components/WorldPosition.h"
#include "../../components/tween/TweenWorldPosition.h"
#include "../../components/debug/DebugName.h"
#include "../../components/tween/TweenData.h"

void TweenWorldPositionSystem::Update(entt::registry *registry) {
    auto tweens = registry->view<TweenData, TweenWorldPosition>();
    for (auto [entity, data, tween] : tweens.each()) {
        auto alpha = data.GetProgress();

        float finalX = Ease::Calculate(data.ease, tween.from.x, tween.to.x, alpha);
        float finalY = Ease::Calculate(data.ease, tween.from.y, tween.to.y, alpha);

        registry->emplace_or_replace<WorldPosition>(data.target, WorldPosition{Vector2 { finalX, finalY }});
    }
}
