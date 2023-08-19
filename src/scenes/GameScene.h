//
// Created by Arya Rakha on 6/5/2023.
//

#ifndef CMAKESFMLPROJECT_GAMESCENE_H
#define CMAKESFMLPROJECT_GAMESCENE_H


#include "Scene.h"
#include "../application/SFMLWindow.h"

class GameScene : public Scene {
protected:
    void RegisterSystems(SystemsHandler *handle) override;

    void OnStart() override;

    void OnUpdate() override;

    void OnFixedUpdate() override;

    void OnRender() override;

private:
    std::shared_ptr<SFMLWindow> sfWindow;

    sf::View gameView;

    void CreatePlayer();

    void CreateBackground();
};


#endif //CMAKESFMLPROJECT_GAMESCENE_H
