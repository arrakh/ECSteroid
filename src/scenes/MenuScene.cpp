//
// Created by Arya Rakha on 8/2/2023.
//

#include <iostream>
#include "MenuScene.h"
#include "../systems/SFMLRenderSystem.h"
#include "../systems/SFMLSpriteSystem.h"
#include "../components/Sprite.h"
#include "../systems/EntityRelationSystem.h"
#include "../systems/ui/SFMLButtonSystem.h"
#include "../systems/ui/SFMLButtonStatesSpriteSystem.h"
#include "../systems/ui/MainMenuUISystem.h"
#include "../systems/ui/SFMLTextSystem.h"

void MenuScene::RegisterSystems(SystemsHandler *handle) {
    handle->Register(new EntityRelationSystem());
    handle->Register(new SFMLButtonSystem());
    handle->Register(new SFMLButtonStatesSpriteSystem());
    handle->Register(new SFMLRenderSystem());
    handle->Register(new SFMLSpriteSystem());
    handle->Register(new SFMLTextSystem());

    handle->Register(new MainMenuUISystem());
}