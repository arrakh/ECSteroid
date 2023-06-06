#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "util/Time.h"
#include "scenes/GameScene.h"

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    Scene* currentScene = new GameScene();

    currentScene->Start();
    float accumulator = 0.f;

    while (window.isOpen())
    {
        Time::updateDeltaTime();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::Resized){
                auto view = window.getView();
                view.setSize(event.size.width, event.size.height);
            }
        }

        float fixedTickRate = Time::fixedDeltaTime();

        accumulator += Time::deltaTime();
        while (accumulator >= fixedTickRate){
            currentScene->FixedUpdate();
            accumulator -= fixedTickRate;
        }

        currentScene->Update();

        window.clear();

        currentScene->Render(&window);

        window.display();
    }

    delete currentScene;
}