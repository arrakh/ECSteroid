//
// Created by Arya Rakha on 9/30/2023.
//

#ifndef ECSTEROID_TWEENBUILDER_H
#define ECSTEROID_TWEENBUILDER_H


#include <functional>
#include "entt/entt.hpp"
#include "Ease.h"

class TweenBuilder {
public:
    explicit TweenBuilder(entt::registry *registry, entt::entity tweenEntity);
    TweenBuilder* SetOnComplete(std::function<void()> onComplete);
    TweenBuilder* SetOnUpdate(std::function<void(float)> onComplete);
    TweenBuilder* SetEase(Ease::Type type);

private:
    entt::registry *registry;
    entt::entity tweenEntity;
};


#endif //ECSTEROID_TWEENBUILDER_H
