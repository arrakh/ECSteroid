#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <entt/entt.hpp>
#include "util/Time.h"
#include "systems/LocalPlayerMovementSystem.h"
#include "systems/RectangleDrawSystem.h"
#include "components/LocalPlayer.h"
#include "components/Position.h"
#include "components/Speed.h"
#include "components/SFMLRectangleShape.h"

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    entt::registry registry;

    //todo: REMOVE THIS AND MAKE BETTER SYSTEM HANDLING
    LocalPlayerMovementSystem moveSystem;
    RectangleDrawSystem rectDrawSystem;

    auto player = registry.create();

    SFMLRectangleShape shape;
    shape.shape.setSize(sf::Vector2f{100.0f, 100.0f});
    shape.shape.setFillColor(sf::Color{255, 0, 0});

    registry.emplace<SFMLRectangleShape>(player, shape);

    registry.emplace<Speed>(player, Speed {100.0f});
    registry.emplace<LocalPlayer>(player, LocalPlayer{});
    registry.emplace<Position>(player, Position {Vector2(0.0f, 0.0f)});

    auto test = registry.create();
    registry.emplace<SFMLRectangleShape>(test, shape);

    registry.emplace<Speed>(test, Speed {50.0f});
    registry.emplace<LocalPlayer>(test, LocalPlayer{});
    registry.emplace<Position>(test, Position {Vector2(300.0f, 0.0f)});


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

        moveSystem.Update(&registry);

        window.clear();

        rectDrawSystem.Render(&registry, &window);

        window.display();
    }
}