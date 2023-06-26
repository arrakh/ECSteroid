//
// Created by Arya Rakha on 6/5/2023.
//

#include "Scene.h"

Scene::Scene() {

}

Scene::~Scene() {
    sysHandle.UnregisterEvents(&registry, &eventListener);
    sysHandle.UnloadSystems();
}

void Scene::Start() {
    RegisterSystems(&sysHandle);
    sysHandle.SortRenderables();
    sysHandle.LoadSystems(&registry);
    sysHandle.RegisterEvents(&registry, &eventListener);
    sysHandle.InjectPublisher(&eventPublisher);

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
    OnRender(renderTarget);
}

void Scene::FinalUpdate() {
    sysHandle.FinalUpdateSystems(&registry);
}

void Scene::LateUpdate() {
    sysHandle.LateUpdateSystems(&registry);
}
