//
// Created by Arya Rakha on 6/11/2023.
//

#include <iostream>
#include "imgui.h"
#include "Box2DDebugDrawSystem.h"
#include "../datatype/Vector2.h"
#include "../application/SFMLWindow.h"

bool Box2DDebugDrawSystem::shouldDraw = true;

void Box2DDebugDrawSystem::Render(entt::registry *registry) {
    if (!shouldDraw) return;

    auto dataView = registry->view<Box2DDebugData, PhysicsBody>();
    for (auto [entity, data, body]: dataView.each()) {
        auto pos = body.body->GetPosition();
        auto rot = body.body->GetAngle();

        data.shape->setOutlineColor(data.outlineColor);
        data.shape->setOutlineThickness(data.outlineSize);

        data.shape->setPosition(Vector2 { pos });
        data.shape->setRotation(rot * 180.f / b2_pi);

        sfWindow->windowPtr->draw(*data.shape);
    }
}

int Box2DDebugDrawSystem::GetRenderOrder() {
    return 200;
}

void Box2DDebugDrawSystem::FixedUpdate(entt::registry *registry) {
    auto defView = registry->view<Box2DDebugDefinition, PhysicsBody>();
    for (auto [entity, definition, body] : defView.each()) {

        auto& fixture = body.fixture;
        auto shape = fixture->GetShape();

        std::shared_ptr<sf::Shape> shapePtr = nullptr;
        b2CircleShape *b2Circle;
        sf::CircleShape circleShape;
        float worldRadius;

        switch (shape->m_type) {
            case b2Shape::Type::e_circle:
                b2Circle = dynamic_cast<b2CircleShape *>(shape);
                worldRadius = b2Circle->m_radius / 0.01f;
                circleShape.setRadius(worldRadius);
                circleShape.setOrigin(worldRadius, worldRadius);
                shapePtr = std::make_shared<sf::CircleShape>(circleShape);
                break;

            case b2Shape::Type::e_polygon:
                auto b2Polygon = dynamic_cast<b2PolygonShape*>(shape);
                sf::ConvexShape convexShape;
                std::size_t maxCount = b2Polygon->m_count;
                convexShape.setPointCount(maxCount);

                for (int i = 0; i < maxCount; ++i) {
                    Vector2 point {b2Polygon->m_vertices[i]};
                    convexShape.setPoint(i, point);
                }

                shapePtr = std::make_shared<sf::ConvexShape>(convexShape);
                break;
        }

        if (shapePtr == nullptr) {
            std::cout << "Trying to create Box2D Debug but could not handle type " << body.shape->m_type << std::endl;
            return;
        }

        shapePtr->setFillColor(sf::Color::Transparent);
        Box2DDebugData data {shapePtr, definition.outlineColor, definition.outlineSize};
        registry->emplace<Box2DDebugData>(entity, data);
    }

    registry->clear<Box2DDebugDefinition>();
}

void Box2DDebugDrawSystem::Update(entt::registry *registry) {
    ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);

    static bool windowOpen;
    if (!ImGui::Begin("Physics Debug Draw", &windowOpen)){
        ImGui::End();
        return;
    }

    ImGui::Checkbox("Draw Bounds", &shouldDraw);

    ImGui::End();
}
