//
// Created by Arya Rakha on 8/10/2023.
//

#include <iostream>
#include "WaveSystem.h"
#include "../components/Asteroid.h"
#include "../events/StartWaveEvent.h"
#include "../util/Random.h"
#include "../application/Application.h"

void WaveSystem::Load(entt::registry *registry) {
    StartWave();
}

void WaveSystem::Unload() {

}

int WaveSystem::GetRandomAsteroidCount() {
    return Random::Range(3, 5);
}

void WaveSystem::FinalUpdate(entt::registry *registry) {
    if (!hasWaveStarted) return;
    auto view = registry->view<Asteroid>();
    if (!view.empty()) return;

    StartWave();
}

void WaveSystem::StartWave() {
    wave++;
    std::cout << "Starting a new Wave ( "<< wave <<" )!\n";

    StartWaveEvent event;
    event.waveNumber = wave;

    int asteroidCount = GetRandomAsteroidCount();
    for (int i = 0; i < asteroidCount; ++i) {
        event.params.push_back(GetCreateParameter());
    }

    publisher->Publish(event);

    hasWaveStarted = true;
}

CreateAsteroidParameter WaveSystem::GetCreateParameter() {
    int randSplitCount = Random::Range(0, 2);

    float randHealth = Random::Range(55.f, 70.f);

    float randSize = Random::Range(70.f, 110.f);
    float doubleSize = randSize * 2;

    float hw = sfWindow->width / 2.f;
    float hh = sfWindow->height / 2.f;

    float x = Random::Range(-hw + doubleSize ,hw - doubleSize);
    float y = Random::Range(-hh + doubleSize ,hh - doubleSize);
    float randDamage = Random::Range(70.f, 90.f);
    float randAngle = Random::Range(0.f, 360.f);
    float randSpeed = Random::Range(60.f, 130.f);
    float randRotSpeed = Random::Range(50.f, 300.f);
    Vector2 randDir = Random::UnitCircle();

    Asteroid def {.size = randSize, .speed = randSpeed, .rotationSpeed = randRotSpeed, .startRotation = randAngle,
            .startHealth = randHealth, .damageOnHit = randDamage, .splitCount = randSplitCount};

    return CreateAsteroidParameter{def, Vector2{x, y},  randDir};
}
