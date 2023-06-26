//
// Created by Arya Rakha on 6/9/2023.
//

#include <entt/entt.hpp>
#include <iostream>
#include "util/Time.h"
#include "scenes/GameScene.h"
#include "Application.h"
#include "imgui-SFML.h"
#include "events/SFMLEvent.h"

float Application::Width = 1920.f;
float Application::Height = 1080.f;
unsigned int Application::Width_u = 1920u;
unsigned int Application::Height_u = 1080u;
std::shared_ptr<sf::RenderWindow> Application::WindowPtr;

void Application::Run() {

    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Width_u, Height_u), "CMake SFML Project");
    WindowPtr = window;
    window->setFramerateLimit(120);
    window->setVerticalSyncEnabled(false);
    auto view = window->getView();
    view.setCenter(0,0);
    window->setView(view);

    auto initialized = ImGui::SFML::Init(*window);


    if (!initialized){
        std::cout << "Can't initialize ImGui - SFML!" << std::endl;
        return;
    }

    Scene* currentScene = new GameScene();

    currentScene->Start();
    float accumulator = 0.f;

    while (window->isOpen())
    {
        Time::updateDeltaTime();

        for (auto event = sf::Event{}; window->pollEvent(event);)
        {
            ImGui::SFML::ProcessEvent(*window, event);

            auto eventPtr = std::make_shared<sf::Event>(event);
            SFMLEvent sfmlEvent {window, eventPtr};

            currentScene->PublishEvent(sfmlEvent);

            if (event.type == sf::Event::Closed)
            {
                window->close();
            }

            if (event.type == sf::Event::Resized){
                auto view = window->getView();
                Width_u = event.size.width;
                Height_u = event.size.height;
                Width = Width_u;
                Height = Height_u;
                view.setSize(Width_u, Height_u);
            }
        }

        ImGui::SFML::Update(*window, Time::deltaSFTime());

        float fixedTickRate = Time::fixedDeltaTime();

        accumulator += Time::deltaTime();
        while (accumulator >= fixedTickRate){
            currentScene->FixedUpdate();
            accumulator -= fixedTickRate;
        }

        currentScene->Update();

        currentScene->LateUpdate();

        window->clear();

        currentScene->Render(window.get());
        ImGui::SFML::Render(*window);

        window->display();

        currentScene->FinalUpdate();
    }

    ImGui::SFML::Shutdown(*window);

    delete currentScene;
}
