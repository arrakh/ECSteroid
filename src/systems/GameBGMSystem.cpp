//
// Created by Arya Rakha on 8/2/2023.
//

#include "GameBGMSystem.h"
#include "../services/SFMLAudioService.h"

void GameBGMSystem::LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) {
    auto audioService = serviceLocator->Locate<SFMLAudioService>();
    audioService->PlayBGM("game.ogg", 40.f);
}
