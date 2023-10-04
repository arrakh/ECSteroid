//
// Created by Arya Rakha on 10/1/2023.
//

#ifndef ECSTEROID_TWEENTESTINGSCENE_H
#define ECSTEROID_TWEENTESTINGSCENE_H


#include "Scene.h"
#include "../application/SFMLWindow.h"

class TweenTestingScene : public Scene {
    void RegisterSystems(SystemsHandler *handle) override;

protected:
    void OnStart() override;

    void OnUpdate() override;

    std::shared_ptr<SFMLWindow> sfWindow;

};


#endif //ECSTEROID_TWEENTESTINGSCENE_H
