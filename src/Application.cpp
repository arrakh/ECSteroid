//
// Created by Arya Rakha on 6/9/2023.
//

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include <iostream>
#include "util/Time.h"
#include "scenes/GameScene.h"
#include "Application.h"
#include "imgui-SFML.h"
#include "Constants.h"

void Application::Run() {
    auto width = Constants::DEFAULT_SCREEN_WIDTH_U;
    auto height = Constants::DEFAULT_SCREEN_HEIGHT_U;

    auto window = sf::RenderWindow{ { width, height }, "CMake SFML Project" };
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    auto initialized = ImGui::SFML::Init(window);

    if (!initialized){
        std::cout << "Can't initialize ImGui - SFML!" << std::endl;
        return;
    }

    Scene* currentScene = new GameScene();

    currentScene->Start();
    float accumulator = 0.f;

    while (window.isOpen())
    {
        Time::updateDeltaTime();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::Resized){
                auto view = window.getView();
                view.setSize(event.size.width, event.size.height);
            }
        }

        ImGui::SFML::Update(window, Time::deltaSFTime());

        float fixedTickRate = Time::fixedDeltaTime();

        accumulator += Time::deltaTime();
        while (accumulator >= fixedTickRate){
            currentScene->FixedUpdate();
            accumulator -= fixedTickRate;
        }

        currentScene->Update();

        window.clear();

        currentScene->Render(&window);
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown(window);

    delete currentScene;
}
