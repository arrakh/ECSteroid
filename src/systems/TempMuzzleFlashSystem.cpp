//
// Created by Arya Rakha on 10/8/2023.
//

#include "TempMuzzleFlashSystem.h"
#include "../events/ShootEvent.h"
#include "../components/MuzzleFlash.h"
#include "../components/WorldPosition.h"
#include "../components/debug/DebugName.h"
#include "../components/Rotation.h"
#include "../components/Sprite.h"
#include "../util/Tweens.h"

void OnShoot(ShootEvent e){
    auto registry = e.registry;
    auto muzzleData = registry->try_get<MuzzleFlash>(e.shooter);

    if (muzzleData == nullptr) {
        std::cout << "Could not get muzzle data from shooter!\n";
        return;
    }

    float animateTime = 0.4f;
    auto muzzleEntity = muzzleData->muzzleEntity;
    auto opacityTween = muzzleData->opacityTween;
    auto scaleTween = muzzleData->scaleTween;

    if (!registry->valid(opacityTween)){
        opacityTween = Tween::Opacity(registry, muzzleEntity, 1, 0, animateTime)
                .SetEase(Ease::Type::OutQuint)
                ->GetEntity();
    } else Tween::ResetTime(registry, opacityTween);

    if (!registry->valid(scaleTween)){
        scaleTween = Tween::Scale(registry, muzzleEntity, Vector2{1, 1}, Vector2{0, 0.3f}, animateTime)
                .SetEase(Ease::Type::OutQuint)
                ->GetEntity();
    } else Tween::ResetTime(registry, scaleTween);

    registry->patch<MuzzleFlash>(e.shooter, [opacityTween, scaleTween](MuzzleFlash &muzzleFlash){
       muzzleFlash.opacityTween = opacityTween;
       muzzleFlash.scaleTween = scaleTween;
    });
}

void TempMuzzleFlashSystem::SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    subscriber->Subscribe<ShootEvent>(&OnShoot);
}

void TempMuzzleFlashSystem::UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    subscriber->Unsubscribe<ShootEvent>(&OnShoot);
}

void CreateMuzzle(entt::registry *registry, entt::entity entity){
    auto muzzle = registry->create();
    registry->emplace<SpriteDefinition>(muzzle, SpriteDefinition {
            .spriteName =  "muzzle-flash", .initialOrder =  10, .pivot = Vector2{0.142f, 0.5f},
            .useCustomDimensions = true, .customWidth = 163.f, .customHeight = 90.f, .alpha = 0
    });

    registry->emplace<DebugName>(muzzle, DebugName{"Muzzle"});
    registry->emplace<WorldPosition>(muzzle, WorldPosition {Vector2(0, 0)});
    registry->emplace<Rotation>(muzzle, Rotation{0});

    registry->emplace<MuzzleFlash>(entity, MuzzleFlash{ 0, 0, muzzle, entt::null, entt::null});
}

void TempMuzzleFlashSystem::Update(entt::registry *registry) {
    auto shootersWithoutMuzzle = registry->view<ShootAbility>(entt::exclude<MuzzleFlash>);

    for (auto [entity, shootAbility] : shootersWithoutMuzzle.each()) {
        CreateMuzzle(registry, entity);
    }

    auto muzzles = registry->view<WorldPosition, Rotation, MuzzleFlash>();

    for (auto [entity, pos, rot, muzzle] : muzzles.each()) {
        Vector2 finalPos = pos.vector;
        registry->patch<WorldPosition>(muzzle.muzzleEntity, [finalPos](WorldPosition &worldPos){ worldPos.vector = finalPos; });

        float finalRot = rot.value;
        registry->patch<Rotation>(muzzle.muzzleEntity, [finalRot](Rotation &worldRot) {worldRot.value = finalRot;});
    }
}
