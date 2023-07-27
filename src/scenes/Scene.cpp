//
// Created by Arya Rakha on 6/5/2023.
//

#include "Scene.h"

Scene::Scene() {

}

Scene::~Scene() {
    systemHandler.UnregisterEvents(&registry, &eventListener);
    systemHandler.UnloadSystems();
}

void Scene::Start(std::shared_ptr<ServiceLocator> serviceLocator) {
    RegisterSystems(&systemHandler);
    systemHandler.SortRenderables();
    systemHandler.InjectServiceLocator(serviceLocator);
    systemHandler.LoadSystems(&registry);
    systemHandler.RegisterEvents(&registry, &eventListener);
    systemHandler.InjectPublisher(&eventPublisher);

    OnStart();
}

void Scene::Update() {
    systemHandler.UpdateSystems(&registry);
    OnUpdate();
}

void Scene::FixedUpdate() {
    systemHandler.FixedUpdateSystems(&registry);
    OnFixedUpdate();
}

void Scene::Render(sf::RenderTarget *renderTarget) {
    systemHandler.RenderSystems(&registry, renderTarget);
    OnRender(renderTarget);
}

void Scene::FinalUpdate() {
    systemHandler.FinalUpdateSystems(&registry);
}

void Scene::LateUpdate() {
    systemHandler.LateUpdateSystems(&registry);
}
