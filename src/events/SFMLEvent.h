//
// Created by Arya Rakha on 6/12/2023.
//

#ifndef ECSTEROID_SFMLEVENT_H
#define ECSTEROID_SFMLEVENT_H

#include "../systems/core/EventSystem.h"
#include <SFML/Graphics.hpp>
#include <memory>

class SFMLEvent : public Event {
public:
    SFMLEvent(const std::shared_ptr<sf::RenderWindow> &window, const std::shared_ptr<sf::Event> &event) : window(
            window), event(event) {}

    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<sf::Event> event;
};


#endif //ECSTEROID_SFMLEVENT_H
