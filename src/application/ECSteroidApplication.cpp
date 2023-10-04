//
// Created by Arya Rakha on 8/2/2023.
//

#include "ECSteroidApplication.h"
#include "../services/SFMLTextureService.h"
#include "../services/SFMLFontService.h"
#include "../services/SFMLAudioService.h"
#include "SFMLImGuiWindow.h"
#include "../scenes/TweenTestingScene.h"

std::unique_ptr<Scene> ECSteroidApplication::GetInitialScene() {
    return std::make_unique<TweenTestingScene>();
}

void ECSteroidApplication::RegisterServices() {
    servicesHandler.Register(new SFMLTextureService());
    servicesHandler.Register(new SFMLFontService());
    servicesHandler.Register(new SFMLAudioService());
}

IWindow* ECSteroidApplication::GetWindow() {
    return new SFMLImGuiWindow();
}
