//
// Created by Arya Rakha on 9/30/2023.
//

#include "Tweens.h"
#include "../components/tween/TweenOpacity.h"
#include "../components/tween/TweenScale.h"

TweenBuilder Tween::PositionOffset(entt::registry *registry, entt::entity target, Vector2 from, Vector2 to, float duration){
    auto entity = registry->create();

    registry->emplace<TweenTarget>(entity, TweenTarget{target});
    registry->emplace<TweenTimer>(entity, TweenTimer{duration});

    auto targetRelation = registry->try_get<Relation>(target);
    bool shouldModifyLocal = targetRelation != nullptr && registry->valid(targetRelation->parent);

    if (shouldModifyLocal) {
        registry->emplace<TweenLocalPosition>(entity, TweenLocalPosition{from, to});
    } else {
        auto posData = registry->try_get<WorldPosition>(target);
        auto pos = posData == nullptr ? Vector2{0,0} : posData->vector;
        registry->emplace<TweenWorldPosition>(entity, TweenWorldPosition{pos + from, pos + to});
    }

    return TweenBuilder {registry, entity};
}

TweenBuilder Tween::Opacity(entt::registry *registry, entt::entity target, float from, float to, float duration) {
    auto entity = registry->create();

    registry->emplace<TweenTarget>(entity, TweenTarget{target});
    registry->emplace<TweenTimer>(entity, TweenTimer{duration});
    registry->emplace<TweenOpacity>(entity, TweenOpacity{from, to});

    return TweenBuilder {registry, entity};
}

TweenBuilder Tween::Scale(entt::registry *registry, entt::entity target, Vector2 from, Vector2 to, float duration){
    auto entity = registry->create();

    registry->emplace<TweenTarget>(entity, TweenTarget{target});
    registry->emplace<TweenTimer>(entity, TweenTimer{duration});
    registry->emplace<TweenScale>(entity, TweenScale{from, to});

    return TweenBuilder {registry, entity};
}

Vector2 Tween::GetAccumulatedWorldPosition(entt::registry *registry, entt::entity entity) {
    auto posData = registry->try_get<WorldPosition>(entity);
    Vector2 pos = posData ? posData->vector : Vector2{0, 0};

    auto relation = registry->try_get<Relation>(entity);
    if (relation && registry->valid(relation->parent)) {
        pos = pos + GetAccumulatedWorldPosition(registry, relation->parent);
    }

    return pos;
}

TweenBuilder Tween::PositionExact(entt::registry *registry, entt::entity target, Vector2 from, Vector2 to, float duration){
    auto entity = registry->create();

    registry->emplace<TweenTarget>(entity, TweenTarget{target});
    registry->emplace<TweenTimer>(entity, TweenTimer{duration});

    auto targetRelation = registry->try_get<Relation>(target);
    bool hasParent = targetRelation != nullptr && registry->valid(targetRelation->parent);

    if (hasParent) {
        Vector2 parentAccumulatedPos = GetAccumulatedWorldPosition(registry, targetRelation->parent);

        Vector2 localFrom = from - parentAccumulatedPos;
        Vector2 localTo = to - parentAccumulatedPos;

        registry->emplace<TweenLocalPosition>(entity, TweenLocalPosition{localFrom, localTo});
    } else {
        registry->emplace<TweenWorldPosition>(entity, TweenWorldPosition{from, to});
    }

    return TweenBuilder {registry, entity};
}