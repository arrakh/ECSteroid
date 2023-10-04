//
// Created by Arya Rakha on 9/30/2023.
//

#ifndef ECSTEROID_TWEENS_H
#define ECSTEROID_TWEENS_H

#include "../datatype/TweenBuilder.h"
#include "../datatype/Vector2.h"
#include "../components/Relation.h"
#include "../components/WorldPosition.h"
#include "../components/tween/TweenLocalPosition.h"
#include "../components/tween/TweenWorldPosition.h"

namespace Tween{

    TweenBuilder PositionOffset(entt::registry *registry, entt::entity target, Vector2 from, Vector2 to, float duration);
    TweenBuilder PositionExact(entt::registry *registry, entt::entity target, Vector2 from, Vector2 to, float duration);
    TweenBuilder Opacity(entt::registry *registry, entt::entity target, float from, float to, float duration);
    TweenBuilder Scale(entt::registry *registry, entt::entity target, Vector2 from, Vector2 to, float duration);
    Vector2 GetAccumulatedWorldPosition(entt::registry *registry, entt::entity entity);
}


#endif //ECSTEROID_TWEENS_H
