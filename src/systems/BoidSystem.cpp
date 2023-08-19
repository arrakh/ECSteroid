//
// Created by Arya Rakha on 7/1/2023.
//

#include <iostream>
#include <random>
#include "BoidSystem.h"
#include "../application/Application.h"
#include "../util/Time.h"
#include "../components/debug/DebugName.h"
#include "../components/Sprite.h"

void BoidSystem::Update(entt::registry *registry) {
    auto view = registry->view<Boid, Position>();

    for (auto [entity, boidData, posData] : view.each()) {
        Vector2 flockVelocity = Flock(registry, boidData, posData, 50, .0003);
        Vector2 alignVelocity = Align(registry, boidData, posData, 50, .01);
        Vector2 avoidVelocity = Avoid(registry, boidData, posData, 20, .001);
        auto newX = boidData.velocity.x + flockVelocity.x + alignVelocity.x + avoidVelocity.x;
        auto newY = boidData.velocity.y + flockVelocity.y + alignVelocity.y + avoidVelocity.y;

        registry->patch<Boid>(entity, [newX, newY](Boid& data){data.velocity = Vector2{newX, newY};});
    }

    for (auto [entity, boidData, posData] : view.each()) {
        auto newPos = posData.vector + (boidData.velocity * Time::deltaTime() * 200);
        registry->patch<Position>(entity, [newPos](Position& data){data.vector = newPos;});
        BounceOffWalls(registry, entity, boidData, posData);
    }
}

void BoidSystem::BounceOffWalls(entt::registry * registry, entt::entity entity, Boid& boid, Position& pos)
{
    float hw = sfWindow->width / 2.f;
    float hh = sfWindow->height / 2.f;

    float pad = 100.f;
    float turn = .5f;
    auto vel = boid.velocity;
    if (pos.vector.x < -hw + pad) vel.x += turn;
    if (pos.vector.x > hw - pad) vel.x -= turn;
    if (pos.vector.y < -hh + pad) vel.y += turn;
    if (pos.vector.y > hh - pad) vel.y -= turn;

    registry->patch<Boid>(entity, [vel](Boid& data){data.velocity = vel;});
}

Vector2 BoidSystem::Flock(entt::registry * registry, Boid& boid, Position& pos, float distance, float power)
{
    float meanX = 0, meanY = 0;
    float count = 0;

    auto view = registry->view<Boid, Position>();
    for (auto [entity, boidData, posData] : view.each()) {
        if (posData.getDistance(pos) > distance) continue;
        meanX += posData.vector.x;
        meanY += posData.vector.y;
        count++;
    }

    if (count > 0) {
        meanX /= count;
        meanY /= count;
    }

    float deltaCenterX = meanX - pos.vector.x;
    float deltaCenterY = meanY - pos.vector.y;
    return Vector2{deltaCenterX * power, deltaCenterY * power};
}

Vector2 BoidSystem::Align(entt::registry * registry, Boid& boid, Position& pos, float distance, float power)
{
    float meanXvel = 0, meanYvel = 0;
    float count = 0;

    auto view = registry->view<Boid, Position>();
    for (auto [entity, boidData, posData] : view.each()) {
        if (posData.getDistance(pos) > distance) continue;
        meanXvel += boidData.velocity.x;
        meanYvel += boidData.velocity.y;
        count++;
    }

    if (count > 0) {
        meanXvel /= count;
        meanYvel /= count;
    }

    float dXvel = meanXvel - boid.velocity.x;
    float dYvel = meanYvel - boid.velocity.y;
    return Vector2{dXvel * power, dYvel * power};
}

Vector2 BoidSystem::Avoid(entt::registry * registry, Boid& boid, Position& pos, float distance, float power)
{
    float sumClosenessX = 0, sumClosenessY = 0;

    auto view = registry->view<Boid, Position>();
    for (auto [entity, boidData, posData] : view.each()) {
        if (posData.getDistance(pos) > distance) continue;
        float closeness = distance - posData.getDistance(pos);
        sumClosenessX += (pos.vector.x - posData.vector.x) * closeness;
        sumClosenessY += (pos.vector.y - posData.vector.y) * closeness;
    }

    return Vector2{sumClosenessX * power, sumClosenessY * power};
}

void BoidSystem::Load(entt::registry *registry) {
    for (int i = 0; i < 300; ++i) {
        auto boid = registry->create();

        Vector2 size{12.f, 12.f};

        registry->emplace<SpriteDefinition>(boid, SpriteDefinition {
                .spriteName =  "meteorGrey_big4", .initialOrder =  1, .initialAngle = 90.f,
                .useCustomDimensions = true, .customWidth = size.y, .customHeight = size.x
        });

        float hw = sfWindow->width / 2.f;
        float hh = sfWindow->height / 2.f;

        std::random_device dev;
        std::mt19937 rng{dev()};

        std::uniform_real_distribution<float> randX(-hw + size.x ,hw - size.x);
        std::uniform_real_distribution<float> randY(-hh + size.y ,hh - size.y);

        std::uniform_real_distribution<float> randVelX(-1.f ,1.f);
        std::uniform_real_distribution<float> randVelY(-1.f ,1.f);

        registry->emplace<Position>(boid, Position {Vector2(randX(rng), randY(rng))});
        registry->emplace<Boid>(boid, Boid {Vector2(randVelX(rng), randVelY(rng))});
    }

    registry->sort<Boid, Position>();
}

void BoidSystem::Unload() {

}
