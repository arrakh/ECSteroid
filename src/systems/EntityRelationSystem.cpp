//
// Created by Arya Rakha on 9/24/2023.
//

#include "EntityRelationSystem.h"
#include "../components/Relation.h"
#include "../components/Position.h"
#include "../components/Rotation.h"
#include "../components/LocalPosition.h"
#include "../components/LocalRotation.h"

void EntityRelationSystem::Update(entt::registry *registry) {
    auto view = registry->view<Relation>();
    for (auto [entity, relationship] : view.each()) {
        if (!registry->valid(relationship.parent)) continue;

        auto childPosition = registry->try_get<Position>(entity);
        auto parentPosition = registry->try_get<Position>(relationship.parent);

        if (childPosition != nullptr && parentPosition != nullptr) {

            auto childLocalPos = registry->try_get<LocalPosition>(entity);
            float childLocalX = childLocalPos != nullptr ? childLocalPos->vector.x : 0.0f;
            float childLocalY = childLocalPos != nullptr ? childLocalPos->vector.y : 0.0f;

            auto parentRot = registry->try_get<Rotation>(relationship.parent);
            float angleRad = parentRot != nullptr ? parentRot->value * M_PI / 180.0f : 0.0f;
            float cosAngle = std::cos(angleRad);
            float sinAngle = std::sin(angleRad);

            float newX = parentPosition->vector.x + (childLocalX * cosAngle - childLocalY * sinAngle);
            float newY = parentPosition->vector.y + (childLocalX * sinAngle + childLocalY * cosAngle);

            registry->patch<Position>(entity, [&newX, &newY](Position& pos){
                pos.vector.x = newX;
                pos.vector.y = newY;
            });
        }

        auto childRotation = registry->try_get<Rotation>(entity);
        auto parentRotation = registry->try_get<Rotation>(relationship.parent);
        if (childRotation != nullptr && parentRotation != nullptr) {
            auto childLocalRotation = registry->try_get<LocalRotation>(entity);
            float childAngle = childLocalRotation != nullptr ? childLocalRotation->value : 0.0f;
            float newAngle = parentRotation->value + childAngle;
            registry->patch<Rotation>(entity, [&newAngle](Rotation& rot){rot.value = newAngle;});
        }
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
