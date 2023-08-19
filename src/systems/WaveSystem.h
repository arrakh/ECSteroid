//
// Created by Arya Rakha on 8/10/2023.
//

#ifndef ECSTEROID_WAVESYSTEM_H
#define ECSTEROID_WAVESYSTEM_H


#include "core/ILoadableSystem.h"
#include "core/IFinalUpdatableSystem.h"
#include "../datatype/CreateAsteroidParameter.h"
#include "core/IEventPublisherSystem.h"
#include "core/IWindowInjectableSystem.h"
#include "../application/SFMLWindow.h"

class WaveSystem : public ILoadableSystem, public IWindowInjectableSystem, public IFinalUpdatableSystem, public IEventPublisherSystem {
public:
    void Load(entt::registry *registry) override;

    void Unload() override;

    void FinalUpdate(entt::registry *registry) override;

    void OnInjectPublisher(Events::Publisher *publisher) override { this->publisher = publisher; }

    void OnInject(std::shared_ptr<IWindow> window) override { sfWindow = std::dynamic_pointer_cast<SFMLWindow>(window);}

private:
    std::shared_ptr<SFMLWindow> sfWindow;
    Events::Publisher *publisher;

    bool hasWaveStarted = false;
    int wave = 0;
    float waveCountDown = 3.f;
    float currentWaveCountDown;

    int GetRandomAsteroidCount();


    void StartWave();

    CreateAsteroidParameter GetCreateParameter();
};


#endif //ECSTEROID_WAVESYSTEM_H
