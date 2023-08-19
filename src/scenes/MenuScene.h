//
// Created by Arya Rakha on 8/2/2023.
//

#ifndef ECSTEROID_MENUSCENE_H
#define ECSTEROID_MENUSCENE_H


#include "Scene.h"

class MenuScene : public Scene {
    void RegisterSystems(SystemsHandler *handle) override;

    void OnStart() override;

    void OnUpdate() override;

    void OnFixedUpdate() override;

    void OnRender() override;

};


#endif //ECSTEROID_MENUSCENE_H
