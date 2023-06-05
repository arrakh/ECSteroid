//
// Created by Arya Rakha on 6/5/2023.
//

#include "Scene.h"

Scene::Scene() { }

Scene::~Scene() {
    sysHandle.UnregisterEvents(&registry);
    sysHandle.UnloadSystems();
}

void Scene::Start() {
    RegisterSystems(&sysHandle);
    sysHandle.SortRenderables();
    sysHandle.LoadSystems(&registry);
    sysHandle.RegisterEvents(&registry);

    OnStart();
}

void Scene::Update() {
    sysHandle.UpdateSystems(&registry);
    OnUpdate();
}

void Scene::FixedUpdate() {
    sysHandle.FixedUpdateSystems(&registry);
    OnFixedUpdate();
}

void Scene::Render(sf::RenderTarget *renderTarget) {
    sysHandle.RenderSystems(&registry, renderTarget);
}
