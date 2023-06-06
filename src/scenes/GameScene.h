//
// Created by Arya Rakha on 6/5/2023.
//

#ifndef CMAKESFMLPROJECT_GAMESCENE_H
#define CMAKESFMLPROJECT_GAMESCENE_H


#include "Scene.h"

class GameScene : public Scene {
protected:
    void RegisterSystems(SystemsHandler *handle) override;

    void OnStart() override;

    void OnUpdate() override;

    void OnFixedUpdate() override;

    void OnRender(sf::RenderTarget *renderTarget) override;

private:
    sf::View gameView;
};


#endif //CMAKESFMLPROJECT_GAMESCENE_H
