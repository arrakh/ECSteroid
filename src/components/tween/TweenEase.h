//
// Created by Arya Rakha on 9/27/2023.
//

#ifndef ECSTEROID_TWEENEASE_H
#define ECSTEROID_TWEENEASE_H

#include "../../datatype/Ease.h"
#include "entt/entity/registry.hpp"

struct TweenEase{
    Ease::Type type;

    static Ease::Type GetType(entt::registry *registry, entt::entity entity){
        auto ease = registry->try_get<TweenEase>(entity);
        if (ease == nullptr) return Ease::Type::Linear;
        return ease->type;
    }
};

#endif //ECSTEROID_TWEENEASE_H
