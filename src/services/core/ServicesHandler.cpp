//
// Created by Arya Rakha on 7/27/2023.
//

#include "ServicesHandler.h"

void ServicesHandler::Load() {
    for (const auto& service : loadableServices) {
        service->Load();
    }
}

void ServicesHandler::Unload() {
    for (const auto& service : loadableServices) {
        service->Unload();
    }
}

void ServicesHandler::Update(float deltaTime) {
    for (const auto& service : updatableServices) {
        service->Update(deltaTime);
    }
}
