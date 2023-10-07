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

std::unordered_set<entt::entity> toDestroyEntities;

void MarkChildrenForDestruction(entt::registry& registry, entt::entity entity) {
    std::vector<entt::entity> stack;
    stack.push_back(entity);

    while (!stack.empty()) {
        entt::entity current = stack.back();
        stack.pop_back();

        toDestroyEntities.insert(current);

        if (registry.any_of<Relation>(current)) {
            auto& relation = registry.get<Relation>(current);
            entt::entity child = relation.first;

            while (child != entt::null) {
                stack.push_back(child);
                if (registry.any_of<Relation>(child)) {
                    child = registry.get<Relation>(child).next;
                } else {
                    child = entt::null;
                }
            }
        }
    }
}

void MarkInvalidParentChildrenForDestruction(entt::registry& registry) {
    auto view = registry.view<Relation>();

    for (entt::entity entity : view) {
        auto& relation = view.get<Relation>(entity);

        if (relation.parent != entt::null && !registry.valid(relation.parent)) {
            MarkChildrenForDestruction(registry, entity);
        }
    }
}

void EntityRelationSystem::EarlyUpdate(entt::registry *registry) {
    MarkInvalidParentChildrenForDestruction(*registry);

    for (auto entity : toDestroyEntities) {
        if (registry->valid(entity)) {
            registry->destroy(entity);
        }
    }
    toDestroyEntities.clear();
}

std::vector<entt::entity> updateStack;

void EntityRelationSystem::UpdateEntityAndChildren(entt::registry& registry, entt::entity entity) {
    updateStack.clear();
    updateStack.push_back(entity);

    while (!updateStack.empty()) {
        entt::entity currentEntity = updateStack.back();
        updateStack.pop_back();

        auto& relationship = registry.get<Relation>(currentEntity);

        auto childPosition = registry.try_get<WorldPosition>(currentEntity);
        auto parentPosition = registry.try_get<WorldPosition>(relationship.parent);

        if (childPosition && parentPosition) {
            auto childLocalPos = registry.try_get<LocalPosition>(currentEntity);
            float childLocalX = childLocalPos ? childLocalPos->vector.x : 0.0f;
            float childLocalY = childLocalPos ? childLocalPos->vector.y : 0.0f;

            auto parentRot = registry.try_get<Rotation>(relationship.parent);
            float angleRad = parentRot ? parentRot->value * M_PI / 180.0f : 0.0f;
            float cosAngle = std::cos(angleRad);
            float sinAngle = std::sin(angleRad);

            float newX = parentPosition->vector.x + (childLocalX * cosAngle - childLocalY * sinAngle);
            float newY = parentPosition->vector.y + (childLocalX * sinAngle + childLocalY * cosAngle);

            registry.patch<WorldPosition>(currentEntity, [&newX, &newY](WorldPosition& pos) {
                pos.vector.x = newX;
                pos.vector.y = newY;
            });
        }

        auto childRotation = registry.try_get<Rotation>(currentEntity);
        auto parentRotation = registry.try_get<Rotation>(relationship.parent);
        if (childRotation && parentRotation) {
            auto childLocalRotation = registry.try_get<LocalRotation>(currentEntity);
            float childAngle = childLocalRotation ? childLocalRotation->value : 0.0f;
            float newAngle = parentRotation->value + childAngle;
            registry.patch<Rotation>(currentEntity, [&newAngle](Rotation& rot) { rot.value = newAngle; });
        }

        entt::entity child = relationship.first;
        while (child != entt::null) {
            updateStack.push_back(child);
            auto childRelation = registry.try_get<Relation>(child);
            child = childRelation ? childRelation->next : entt::null;
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

    if (auto& existingRelation = registry->get_or_emplace<Relation>(child); existingRelation.parent != entt::null) {
        auto& prevParentRelation = registry->get<Relation>(existingRelation.parent);
        if (prevParentRelation.first == child) {
            prevParentRelation.first = existingRelation.next;
        } else {
            if (existingRelation.prev != entt::null) {
                registry->get<Relation>(existingRelation.prev).next = existingRelation.next;
            }
            if (existingRelation.next != entt::null) {
                registry->get<Relation>(existingRelation.next).prev = existingRelation.prev;
            }
        }
        prevParentRelation.children--;
    }

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


