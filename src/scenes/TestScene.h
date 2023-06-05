//
// Created by Arya Rakha on 6/5/2023.
//

#ifndef CMAKESFMLPROJECT_TESTSCENE_H
#define CMAKESFMLPROJECT_TESTSCENE_H


#include "Scene.h"

class TestScene : public Scene {
protected:
    void RegisterSystems(SystemsHandler *handle) override;

    void OnStart() override;

    void OnUpdate() override;

    void OnFixedUpdate() override;
};


#endif //CMAKESFMLPROJECT_TESTSCENE_H
