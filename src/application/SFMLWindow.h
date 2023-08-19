//
// Created by Arya Rakha on 8/19/2023.
//

#ifndef ECSTEROID_SFMLWINDOW_H
#define ECSTEROID_SFMLWINDOW_H


#include <memory>
#include "IWindow.h"
#include "SFML/Graphics.hpp"

class SFMLWindow : public IWindow {
public:
    bool TryInitialize(ServiceLocator& serviceLocator) override;

    bool IsOpen() const override;

    void End() override;

    void PollEvents() override;

    void Clear() override;

    void Render() override;

    unsigned int width_u = 1920;
    unsigned int height_u = 1080;
    float width = 1920;
    float height = 1080;

    std::shared_ptr<sf::RenderWindow> windowPtr;

protected:
    virtual void OnEventPolled(sf::Event& event) = 0;
    virtual void OnPostPollEvents() = 0;
    virtual void OnPreRender() = 0;

private:

};


#endif //ECSTEROID_SFMLWINDOW_H
