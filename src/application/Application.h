//
// Created by Arya Rakha on 6/9/2023.
//

#ifndef CMAKESFMLPROJECT_APPLICATION_H
#define CMAKESFMLPROJECT_APPLICATION_H

#include <memory>
#include "../scenes/GameScene.h"
#include "../services/core/ServicesHandler.h"
#include "../services/core/ServiceLocator.h"
#include "IWindow.h"

class Application {
public:
    void Run();

    float fixedTickAccumulator = 0;

    void GameLoop();

    template <typename Scene>
    static void ChangeScene() {
        nextScene = std::make_unique<Scene>();
        currentScene->shouldEnd = true;
    }

protected:
    virtual std::unique_ptr<Scene> GetInitialScene() = 0;
    virtual void RegisterServices() = 0;
    virtual IWindow* GetWindow() = 0;
    ServicesHandler servicesHandler;


private:
    std::shared_ptr<ServiceLocator> serviceLocator;
    std::shared_ptr<IWindow> window;

    static std::unique_ptr<Scene> currentScene;
    static std::unique_ptr<Scene> nextScene;

};


#endif //CMAKESFMLPROJECT_APPLICATION_H
