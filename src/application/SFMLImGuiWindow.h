//
// Created by Arya Rakha on 8/19/2023.
//

#ifndef ECSTEROID_SFMLIMGUIWINDOW_H
#define ECSTEROID_SFMLIMGUIWINDOW_H


#include "SFMLWindow.h"

class SFMLImGuiWindow : public SFMLWindow {
public:
    bool TryInitialize(ServiceLocator& serviceLocator) override;

    void End() override;

protected:
    void OnPreRender() override;

protected:
    void OnPostPollEvents() override;

protected:
    void OnEventPolled(sf::Event& event) override;

};


#endif //ECSTEROID_SFMLIMGUIWINDOW_H
