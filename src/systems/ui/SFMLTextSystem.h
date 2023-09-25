//
// Created by Arya Rakha on 9/24/2023.
//

#ifndef ECSTEROID_SFMLTEXTSYSTEM_H
#define ECSTEROID_SFMLTEXTSYSTEM_H


#include "../core/IRenderableSystem.h"
#include "../core/IUpdatableSystem.h"
#include "../../components/SFMLText.h"
#include "../core/ILocateServicesSystem.h"
#include "../../services/SFMLFontService.h"

class SFMLTextSystem : public IUpdatableSystem, public ILocateServicesSystem {
public:
    void LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) override;
    void Update(entt::registry *registry) override;

private:
    void CreateObject(entt::registry *registry, entt::entity entity, SFMLText &text);

    std::shared_ptr<SFMLFontService> fontService;
};


#endif //ECSTEROID_SFMLTEXTSYSTEM_H
