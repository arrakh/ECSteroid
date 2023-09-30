//
// Created by Arya Rakha on 9/30/2023.
//

#include "SFMLTweenOpacitySystem.h"
#include "../../components/SFMLSprite.h"
#include "../../components/tween/TweenOpacity.h"
#include "../../components/tween/TweenEase.h"
#include "../../components/tween/TweenTimer.h"
#include "../../components/SFMLText.h"
#include "../../components/tween/TweenTarget.h"

void SFMLTweenOpacitySystem::Update(entt::registry *registry) {
    auto sprites = registry->view<TweenTarget, TweenOpacity, TweenTimer>();

    for (auto [entity, target, tween, timer] : sprites.each()) {
        auto sprite = registry->try_get<SFMLSprite>(target.entity);
        if (sprite == nullptr) continue;

        auto ease = TweenEase::GetType(registry, entity);
        auto alpha = Ease::Calculate(ease, tween.normalizedFrom, tween.normalizedTo, timer.GetProgress());
        auto color = sprite->sprite->getColor();
        color.a = 255 * alpha;

        sprite->sprite->setColor(color);
    }

    auto texts = registry->view<TweenTarget, TweenOpacity, TweenTimer>();

    for (auto [entity, target, tween, timer] : texts.each()) {
        auto text = registry->try_get<SFMLTextObject>(target.entity);
        if (text == nullptr) continue;

        auto ease = TweenEase::GetType(registry, entity);
        auto alpha = Ease::Calculate(ease, tween.normalizedFrom, tween.normalizedTo, timer.GetProgress());
        auto fillColor = text->sfText->getFillColor();
        auto outlineColor = text->sfText->getOutlineColor();
        fillColor.a = 255 * alpha;
        outlineColor.a = 255 * alpha;

        text->sfText->setFillColor(fillColor);
        text->sfText->setOutlineColor(outlineColor);
    }
}
