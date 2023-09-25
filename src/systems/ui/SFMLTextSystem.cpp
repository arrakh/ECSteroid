//
// Created by Arya Rakha on 9/24/2023.
//

#include "SFMLTextSystem.h"
#include "../../components/SFMLDrawable.h"
#include "../../components/SFMLTransformable.h"


void SFMLTextSystem::Update(entt::registry *registry) {
    auto texts = registry->view<SFMLText>();
    for (auto [entity, text] : texts.each()){
        auto textObj = registry->try_get<SFMLTextObject>(entity);
        if (textObj == nullptr) {
            CreateObject(registry, entity, text);
            textObj = &registry->get<SFMLTextObject>(entity);
        }

        textObj->sfText->setString(text.text);
        textObj->sfText->setFillColor(text.color);
        auto bounds = textObj->sfText->getLocalBounds();
        textObj->sfText->setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
    }
}

void SFMLTextSystem::CreateObject(entt::registry *registry, entt::entity entity, SFMLText &text){
    auto font = fontService->Get(text.fontName);
    auto sfText = std::make_shared<sf::Text>(text.text, *font, text.size);

    auto textObj = SFMLTextObject {sfText};

    registry->emplace<SFMLTextObject>(entity, textObj);
    registry->emplace<SFMLTransformable>(entity, SFMLTransformable{sfText});
    registry->emplace<SFMLDrawable>(entity, SFMLDrawable{text.drawOrder, sfText});
}

void SFMLTextSystem::LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) {
    fontService = serviceLocator->Locate<SFMLFontService>();
}
