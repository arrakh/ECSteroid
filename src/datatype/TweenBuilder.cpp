//
// Created by Arya Rakha on 9/30/2023.
//

#include "TweenBuilder.h"
#include "../components/tween/TweenEase.h"

TweenBuilder::TweenBuilder(entt::registry *registry, entt::entity tweenEntity) : registry(registry), tweenEntity(tweenEntity) {}

TweenBuilder *TweenBuilder::SetOnComplete(std::function<void()> onComplete) {

    return this;
}

TweenBuilder *TweenBuilder::SetOnUpdate(std::function<void(float)> onComplete) {
    return this;
}

TweenBuilder *TweenBuilder::SetEase(Ease::Type type) {
    registry->emplace<TweenEase>(tweenEntity, TweenEase{type});
    return this;
}
