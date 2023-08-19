//
// Created by Arya Rakha on 8/13/2023.
//

#ifndef ECSTEROID_BUTTON_H
#define ECSTEROID_BUTTON_H


#include <functional>
#include "SFML/Graphics.hpp"

class Button {
public:
    Button(sf::Vector2f position, sf::Texture& normalTexture, sf::Texture& hoverTexture,
           std::function<void()> onClickedCallback = nullptr)
            : normalTexture_(normalTexture), hoverTexture_(hoverTexture), onClickedCallback_(onClickedCallback) {

        sprite_.setTexture(normalTexture_);
        sprite_.setPosition(position);
    }

    void setParentText(sf::Text& parentText) {
        parentText_ = &parentText;
    }

    void handleEvent(sf::Event event, sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseMoved) {
            if (sprite_.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                sprite_.setTexture(hoverTexture_);
                if (parentText_ != nullptr) {
                    parentText_->setFillColor(sf::Color::Green); // Adjust as needed
                }
            } else {
                sprite_.setTexture(normalTexture_);
                if (parentText_ != nullptr) {
                    parentText_->setFillColor(sf::Color::White); // Adjust as needed
                }
            }
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (sprite_.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) && onClickedCallback_) {
                onClickedCallback_();
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite_);
    }

private:
    sf::Sprite sprite_;
    sf::Texture& normalTexture_;
    sf::Texture& hoverTexture_;
    std::function<void()> onClickedCallback_;
    sf::Text* parentText_ = nullptr; // Pointer to parent text, if any
};


#endif //ECSTEROID_BUTTON_H
