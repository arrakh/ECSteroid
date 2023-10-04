//
// Created by Arya Rakha on 9/30/2023.
//

#include "SFMLTweenOpacitySystem.h"
#include "../../components/SFMLSprite.h"
#include "../../components/tween/TweenOpacity.h"
#include "../../components/SFMLText.h"
#include "../../components/tween/TweenData.h"

void SFMLTweenOpacitySystem::Update(entt::registry *registry) {
    auto sprites = registry->view<TweenData, TweenOpacity>();

    for (auto [entity, data, tween] : sprites.each()) {
        auto sprite = registry->try_get<SFMLSprite>(data.target);
        if (sprite == nullptr) continue;

        auto alpha = Ease::Calculate(data.ease, tween.normalizedFrom, tween.normalizedTo, data.GetProgress());
        auto color = sprite->sprite->getColor();
        color.a = 255 * alpha;

        sprite->sprite->setColor(color);
    }

    auto texts = registry->view<TweenData, TweenOpacity>();

    for (auto [entity, data, tween] : texts.each()) {
        auto text = registry->try_get<SFMLTextObject>(data.target);
        if (text == nullptr) continue;

        auto alpha = Ease::Calculate(data.ease, tween.normalizedFrom, tween.normalizedTo, data.GetProgress());
        auto fillColor = text->sfText->getFillColor();
        auto outlineColor = text->sfText->getOutlineColor();
        fillColor.a = 255 * alpha;
        outlineColor.a = 255 * alpha;

        text->sfText->setFillColor(fillColor);
        text->sfText->setOutlineColor(outlineColor);
    }
}
