//
// Created by Arya Rakha on 10/8/2023.
//

#include "MainMenuBGMSystem.h"
#include "../services/SFMLAudioService.h"

void MainMenuBGMSystem::LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) {
    auto audio = serviceLocator->Locate<SFMLAudioService>();
    audio->PlayBGM("menu.ogg", 40.f);

}
