//
// Created by Arya Rakha on 6/5/2023.
//

#ifndef CMAKESFMLPROJECT_SCENE_H
#define CMAKESFMLPROJECT_SCENE_H


#include "../systems/core/SystemsHandler.h"

class Scene {
public:
    Scene();
    virtual ~Scene();
    void Start();
    void Update();
    void FixedUpdate();
    void Render(sf::RenderTarget* renderTarget);

protected:
    virtual void RegisterSystems(SystemsHandler* handle) = 0;
    virtual void OnStart() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnFixedUpdate() = 0;
    virtual void OnRender(sf::RenderTarget* renderTarget) = 0;

    entt::registry registry;

private:
    SystemsHandler sysHandle;
};


#endif //CMAKESFMLPROJECT_SCENE_H
