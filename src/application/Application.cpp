//
// Created by Arya Rakha on 6/9/2023.
//

#include <iostream>
#include "../util/Time.h"
#include "Application.h"
#include "imgui-SFML.h"
#include "../events/SFMLEvent.h"

std::unique_ptr<Scene> Application::currentScene;
std::unique_ptr<Scene> Application::nextScene;

void Application::Run() {
    serviceLocator = std::make_shared<ServiceLocator>(&servicesHandler);
    RegisterServices();
    servicesHandler.Load();

    window = std::shared_ptr<IWindow>(GetWindow());
    if (!window->TryInitialize(*serviceLocator)){
        std::cout << "Can't initialize Window!\n";
        return;
    }

    currentScene = GetInitialScene();

    while (window->IsOpen())
    {
        currentScene->Start(window, serviceLocator);
        fixedTickAccumulator = 0.f;

        while (!currentScene->shouldEnd && window->IsOpen())
            GameLoop();

        if (nextScene == nullptr) break;

        currentScene = std::move(nextScene);
        nextScene = nullptr;
    }

    servicesHandler.Unload();

    window->End();
}

void Application::GameLoop() {
    Time::updateDeltaTime();

    servicesHandler.Update(Time::deltaTime());

    window->PollEvents();

    float fixedTickRate = Time::fixedDeltaTime();

    fixedTickAccumulator += Time::deltaTime();
    while (fixedTickAccumulator >= fixedTickRate){
        currentScene->FixedUpdate();
        fixedTickAccumulator -= fixedTickRate;
    }

    currentScene->EarlyUpdate();

    currentScene->Update();

    currentScene->LateUpdate();

    window->Clear();

    currentScene->Render();

    window->Render();

    currentScene->FinalUpdate();
}
