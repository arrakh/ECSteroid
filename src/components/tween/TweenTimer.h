//
// Created by Arya Rakha on 9/27/2023.
//

#ifndef ECSTEROID_TWEENTIMER_H
#define ECSTEROID_TWEENTIMER_H

#include <functional>

struct TweenTimer{
    double totalTime = 0;
    double currentTime = 0;

    double GetProgress() const {
        double progress = currentTime / totalTime;
        return std::max(0.0, std::min(1.0, progress));
    }
};

#endif //ECSTEROID_TWEENTIMER_H
