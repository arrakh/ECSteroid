#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "util/Time.h"
#include "scenes/TestScene.h"

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    TestScene testScene;

    testScene.Start();

    while (window.isOpen())
    {
        Time::updateDeltaTime();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        testScene.Update();

        window.clear();

        testScene.Render(&window);

        window.display();
    }
}