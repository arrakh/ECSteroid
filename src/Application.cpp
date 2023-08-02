//
// Created by Arya Rakha on 6/9/2023.
//

#include <iostream>
#include "util/Time.h"
#include "Application.h"
#include "imgui-SFML.h"
#include "events/SFMLEvent.h"
#include "services/SFMLTextureService.h"
#include "services/SFMLFontService.h"
#include "services/SFMLAudioService.h"

float Application::Width = 1920.f;
float Application::Height = 1080.f;
unsigned int Application::Width_u = 1920u;
unsigned int Application::Height_u = 1080u;
std::shared_ptr<sf::RenderWindow> Application::WindowPtr;

void Application::Run() {

    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Width_u, Height_u), "CMake SFML Project");
    WindowPtr = window;
    WindowPtr->setFramerateLimit(120);
    WindowPtr->setVerticalSyncEnabled(false);
    auto view = window->getView();
    view.setCenter(0,0);
    WindowPtr->setView(view);

    auto initialized = ImGui::SFML::Init(*window);


    if (!initialized){
        std::cout << "Can't initialize ImGui - SFML!\n";
        return;
    }

    serviceLocator = std::make_shared<ServiceLocator>(&servicesHandler);

    RegisterServices();

    servicesHandler.Load();

    while (WindowPtr->isOpen())
    {
        Scene* currentScene = new GameScene();

        currentScene->Start(serviceLocator);
        fixedTickAccumulator = 0.f;

        while (!currentScene->ShouldEnd() && WindowPtr->isOpen())
            GameLoop(currentScene);

        delete currentScene;
    }

    servicesHandler.Unload();

    ImGui::SFML::Shutdown(*WindowPtr);
}

void Application::GameLoop(Scene *currentScene) {
    Time::updateDeltaTime();

    servicesHandler.Update(Time::deltaTime());

    for (auto event = sf::Event{}; WindowPtr->pollEvent(event);)
    {
        ImGui::SFML::ProcessEvent(*WindowPtr, event);

        auto eventPtr = std::make_shared<sf::Event>(event);
        SFMLEvent sfmlEvent {WindowPtr, eventPtr};

        currentScene->PublishEvent(sfmlEvent);

        if (event.type == sf::Event::Closed)
        {
            WindowPtr->close();
        }

        if (event.type == sf::Event::Resized){
            auto view = WindowPtr->getView();
            Width_u = event.size.width;
            Height_u = event.size.height;
            Width = Width_u;
            Height = Height_u;
            view.setSize(Width_u, Height_u);
        }
    }

    ImGui::SFML::Update(*WindowPtr, Time::deltaSFTime());

    float fixedTickRate = Time::fixedDeltaTime();

    fixedTickAccumulator += Time::deltaTime();
    while (fixedTickAccumulator >= fixedTickRate){
        currentScene->FixedUpdate();
        fixedTickAccumulator -= fixedTickRate;
    }

    currentScene->Update();

    currentScene->LateUpdate();

    WindowPtr->clear();

    currentScene->Render(WindowPtr.get());
    ImGui::SFML::Render(*WindowPtr);

    WindowPtr->display();

    currentScene->FinalUpdate();
}

void Application::RegisterServices() {
    servicesHandler.Register(new SFMLTextureService());
    servicesHandler.Register(new SFMLFontService());
    servicesHandler.Register(new SFMLAudioService());
}
