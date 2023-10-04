//
// Created by Arya Rakha on 10/3/2023.
//

#ifndef ECSTEROID_TWEENDATA_H
#define ECSTEROID_TWEENDATA_H

#include "entt/entity/entity.hpp"
#include "../../datatype/Ease.h"

struct TweenData {
    entt::entity target;
    double totalTime = 0;
    Ease::Type ease = Ease::Type::Linear;

    double currentTime = 0;

    double GetProgress() const {
        double progress = currentTime / totalTime;
        return std::max(0.0, std::min(1.0, progress));
    }


};

#endif //ECSTEROID_TWEENDATA_H
