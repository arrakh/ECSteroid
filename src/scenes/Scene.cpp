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

void Scene::Start(std::shared_ptr<IWindow> window, std::shared_ptr<ServiceLocator> serviceLocator) {
    this->window = window;

    RegisterSystems(&systemHandler);
    systemHandler.SortRenderables();
    systemHandler.InjectWindow(window);
    systemHandler.InjectServiceLocator(serviceLocator);
    systemHandler.RegisterEvents(&registry, &eventListener);
    systemHandler.InjectPublisher(&eventPublisher);
    systemHandler.LoadSystems(&registry);

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

void Scene::Render() {
    systemHandler.RenderSystems(&registry);
    OnRender();
}

void Scene::FinalUpdate() {
    systemHandler.FinalUpdateSystems(&registry);
}

void Scene::EarlyUpdate() {
    systemHandler.EarlyUpdateSystems(&registry);
}

void Scene::LateUpdate() {
    systemHandler.LateUpdateSystems(&registry);
}
