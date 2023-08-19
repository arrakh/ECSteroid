//
// Created by Arya Rakha on 8/19/2023.
//

#include "SFMLWindow.h"

bool SFMLWindow::TryInitialize(ServiceLocator& serviceLocator) {
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width_u, height_u), "ECSteroid");
    windowPtr = window;
    windowPtr->setFramerateLimit(120);
    windowPtr->setVerticalSyncEnabled(false);
    auto view = window->getView();
    view.setCenter(0,0);
    windowPtr->setView(view);
    return true;
}

bool SFMLWindow::IsOpen() const {
    return windowPtr->isOpen();
}

void SFMLWindow::End() {

}

void SFMLWindow::PollEvents() {
    for (auto event = sf::Event{}; windowPtr->pollEvent(event);)
    {
        OnEventPolled(event);

        if (event.type == sf::Event::Closed)
        {
            windowPtr->close();
        }

        if (event.type == sf::Event::Resized){
            auto view = windowPtr->getView();
            width_u = event.size.width;
            height_u = event.size.height;
            width = width_u;
            height = height_u;
            view.setSize(width_u, height_u);
        }
    }

    OnPostPollEvents();
}

void SFMLWindow::Clear() {
    windowPtr->clear();
}

void SFMLWindow::Render() {
    OnPreRender();
    windowPtr->display();
}
