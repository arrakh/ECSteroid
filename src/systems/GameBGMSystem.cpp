//
// Created by Arya Rakha on 8/2/2023.
//

#include "GameBGMSystem.h"


void GameBGMSystem::LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) {
    audioService = serviceLocator->Locate<SFMLAudioService>();
}

void GameBGMSystem::Load(entt::registry *registry) {
    audioService->PlayBGM("game.ogg", 40.f);
}

void GameBGMSystem::Unload() {
    audioService->StopBGM();
}
