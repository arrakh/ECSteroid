//
// Created by Arya Rakha on 10/7/2023.
//

#ifndef ECSTEROID_MUZZLEFLASH_H
#define ECSTEROID_MUZZLEFLASH_H

struct MuzzleFlash {
    float totalTime = 0;
    float timer = 0;
    entt::entity muzzleEntity;
    entt::entity opacityTween;
    entt::entity scaleTween;
};

#endif //ECSTEROID_MUZZLEFLASH_H
