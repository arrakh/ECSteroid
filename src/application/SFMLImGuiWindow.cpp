//
// Created by Arya Rakha on 8/19/2023.
//

#include <iostream>
#include "SFMLImGuiWindow.h"
#include "imgui-SFML.h"
#include "../util/Time.h"

bool SFMLImGuiWindow::TryInitialize(ServiceLocator &serviceLocator) {
    bool initialized = SFMLWindow::TryInitialize(serviceLocator);
    if (!initialized) return false;

    auto imguiInit = ImGui::SFML::Init(*windowPtr);
    if (!imguiInit){
        std::cout << "Can't initialize ImGui - SFML!\n";
        return false;
    }

    return true;
}

void SFMLImGuiWindow::End() {
    SFMLWindow::End();
    ImGui::SFML::Shutdown(*windowPtr);
}

void SFMLImGuiWindow::OnEventPolled(sf::Event& event) {
    ImGui::SFML::ProcessEvent(*windowPtr, event);
}

void SFMLImGuiWindow::OnPostPollEvents() {
    ImGui::SFML::Update(*windowPtr, Time::deltaSFTime());
}

void SFMLImGuiWindow::OnPreRender() {
    ImGui::SFML::Render(*windowPtr);
}
