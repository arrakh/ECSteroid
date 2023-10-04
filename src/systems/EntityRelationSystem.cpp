//
// Created by Arya Rakha on 9/24/2023.
//

#include <iostream>
#include "EntityRelationSystem.h"
#include "../components/Relation.h"
#include "../components/WorldPosition.h"
#include "../components/Rotation.h"
#include "../components/LocalPosition.h"
#include "../components/LocalRotation.h"
#include "../components/debug/DebugName.h"

void EntityRelationSystem::UpdateEntityAndChildren(entt::registry& registry, entt::entity entity) {
    auto& relationship = registry.get<Relation>(entity);

    auto childPosition = registry.try_get<WorldPosition>(entity);
    auto parentPosition = registry.try_get<WorldPosition>(relationship.parent);

    if (childPosition != nullptr && parentPosition != nullptr) {
        auto childLocalPos = registry.try_get<LocalPosition>(entity);
        float childLocalX = childLocalPos != nullptr ? childLocalPos->vector.x : 0.0f;
        float childLocalY = childLocalPos != nullptr ? childLocalPos->vector.y : 0.0f;

        auto parentRot = registry.try_get<Rotation>(relationship.parent);
        float angleRad = parentRot != nullptr ? parentRot->value * M_PI / 180.0f : 0.0f;
        float cosAngle = std::cos(angleRad);
        float sinAngle = std::sin(angleRad);

        float newX = parentPosition->vector.x + (childLocalX * cosAngle - childLocalY * sinAngle);
        float newY = parentPosition->vector.y + (childLocalX * sinAngle + childLocalY * cosAngle);

        registry.patch<WorldPosition>(entity, [&newX, &newY](WorldPosition& pos) {
            pos.vector.x = newX;
            pos.vector.y = newY;
        });
    }

    auto childRotation = registry.try_get<Rotation>(entity);
    auto parentRotation = registry.try_get<Rotation>(relationship.parent);
    if (childRotation != nullptr && parentRotation != nullptr) {
        auto childLocalRotation = registry.try_get<LocalRotation>(entity);
        float childAngle = childLocalRotation != nullptr ? childLocalRotation->value : 0.0f;
        float newAngle = parentRotation->value + childAngle;
        registry.patch<Rotation>(entity, [&newAngle](Rotation& rot) { rot.value = newAngle; });
    }

    // Now, recursively update the children of the current entity
    entt::entity child = relationship.first;
    while (child != entt::null) {
        UpdateEntityAndChildren(registry, child);

        auto childRelation = registry.try_get<Relation>(child);
        if (childRelation) {
            child = childRelation->next;
        } else {
            child = entt::null;
        }
    }
}

void EntityRelationSystem::Update(entt::registry *registry) {
    auto view = registry->view<Relation>();

    for (auto [entity, relation] : view.each()) {
        if (registry->valid(relation.parent)) continue;
        UpdateEntityAndChildren(*registry, entity);
    }
}

void EntityRelationSystem::Assign(entt::registry *registry, entt::entity parent, entt::entity child) {
    if (!registry->valid(parent) || !registry->valid(child)) return;

    auto& relationship = registry->get_or_emplace<Relation>(child);
    relationship.parent = parent;

    auto& parentRelationship = registry->get_or_emplace<Relation>(parent);
    if (parentRelationship.children == 0) {
        parentRelationship.first = child;
    } else {
        auto& siblingRelationship = registry->get<Relation>(parentRelationship.first);
        siblingRelationship.prev = child;
        relationship.next = parentRelationship.first;
        parentRelationship.first = child;
    }
    parentRelationship.children++;
}

void OnParentDestroyed(entt::registry &registry, entt::entity entity) {
    auto relation = registry.try_get<Relation>(entity);
    if (relation == nullptr) return;

    entt::entity curr = relation->first;

    while (curr != entt::null) {
        entt::entity nextEntity = entt::null;

        if (registry.valid(curr) && registry.any_of<Relation>(curr)) {
            auto& childRelation = registry.get<Relation>(curr);
            nextEntity = childRelation.next;
        }

        registry.destroy(curr);
        curr = nextEntity;
    }
}

void EntityRelationSystem::SubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    registry->on_destroy<Relation>().connect<&OnParentDestroyed>();
}

void EntityRelationSystem::UnsubscribeEvents(entt::registry *registry, Events::Subscriber *subscriber) {
    registry->on_destroy<Relation>().disconnect<&OnParentDestroyed>();
}


