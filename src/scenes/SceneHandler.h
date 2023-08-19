//
// Created by Arya Rakha on 8/2/2023.
//

#ifndef ECSTEROID_SCENEHANDLER_H
#define ECSTEROID_SCENEHANDLER_H


#include "Scene.h"

class SceneHandler {
public:
    template<typename TScene> void ChangeScene(){

    }

    void MainLoop();
private:
    std::unique_ptr<Scene> currentScene;
    std::unique_ptr<Scene> nextScene;
};


#endif //ECSTEROID_SCENEHANDLER_H
