//
// Created by Arya Rakha on 6/5/2023.
//

#ifndef CMAKESFMLPROJECT_SCENE_H
#define CMAKESFMLPROJECT_SCENE_H


#include "../systems/core/SystemsHandler.h"
#include "../services/core/ServiceLocator.h"
#include "../application/IWindow.h"

class Scene {
public:
    Scene();
    virtual ~Scene();
    void Start(std::shared_ptr<IWindow> window, std::shared_ptr<ServiceLocator> serviceLocator);
    void Update();
    void FixedUpdate();
    void FinalUpdate();
    void LateUpdate();
    void Render();

    template<typename EventType> void PublishEvent(const EventType& event) { eventPublisher.Publish(event); }

    bool shouldEnd = false;

protected:
    virtual void RegisterSystems(SystemsHandler* handle) = 0;
    virtual void OnStart() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnFixedUpdate() = 0;
    virtual void OnRender() = 0;

    entt::registry registry;
    std::shared_ptr<IWindow> window;

private:
    std::shared_ptr<ServiceLocator> serviceLocator;
    SystemsHandler systemHandler;
    EventMap eventMap;
    Events::Subscriber eventListener {&eventMap };
    Events::Publisher eventPublisher { &eventMap };
};


#endif //CMAKESFMLPROJECT_SCENE_H
