//
// Created by Arya Rakha on 6/5/2023.
//

#ifndef CMAKESFMLPROJECT_SYSTEMSHANDLER_H
#define CMAKESFMLPROJECT_SYSTEMSHANDLER_H


#include "ILoadableSystem.h"
#include "IRenderableSystem.h"
#include "IUpdatableSystem.h"
#include "IFixedUpdatableSystem.h"
#include "IEventSubscriberSystem.h"
#include "EventSystem.h"
#include "IEventPublisherSystem.h"
#include "IFinalUpdatableSystem.h"
#include "ILateUpdatableSystem.h"

class SystemsHandler {
private:
    std::vector<ILoadableSystem*> loadables;
    std::vector<IRenderableSystem*> renderables;
    std::vector<IUpdatableSystem*> updatables;
    std::vector<IFixedUpdatableSystem*> fixedUpdatables;
    std::vector<IFinalUpdatableSystem*> finalUpdatables;
    std::vector<ILateUpdatableSystem*> lateUpdatables;
    std::vector<IEventSubscriberSystem*> eventRegistrables;
    std::vector<IEventPublisherSystem*> eventPublishers;

public:
    template<typename T>
    void RegisterSystem(T *system) {
        if constexpr (std::is_base_of_v<IEventSubscriberSystem, T>) eventRegistrables.push_back(std::move(system));
        if constexpr (std::is_base_of_v<IEventPublisherSystem, T>) eventPublishers.push_back(std::move(system));
        if constexpr (std::is_base_of_v<IFixedUpdatableSystem, T>) fixedUpdatables.push_back(std::move(system));
        if constexpr (std::is_base_of_v<IFinalUpdatableSystem, T>) finalUpdatables.push_back(std::move(system));
        if constexpr (std::is_base_of_v<ILateUpdatableSystem, T>) lateUpdatables.push_back(std::move(system));
        if constexpr (std::is_base_of_v<IRenderableSystem, T>) renderables.push_back(std::move(system));
        if constexpr (std::is_base_of_v<IUpdatableSystem, T>) updatables.push_back(std::move(system));
        if constexpr (std::is_base_of_v<ILoadableSystem, T>) loadables.push_back(std::move(system));
    }

    void UpdateSystems(entt::registry* registry);
    void FixedUpdateSystems(entt::registry* registry);
    void FinalUpdateSystems(entt::registry* registry);
    void LateUpdateSystems(entt::registry* registry);
    void RenderSystems(entt::registry* registry, sf::RenderTarget* renderTarget);
    void RegisterEvents(entt::registry* registry, Events::Subscriber* listener);
    void UnregisterEvents(entt::registry* registry, Events::Subscriber* listener);
    void InjectPublisher(Events::Publisher* publisher);
    void LoadSystems(entt::registry* registry);
    void UnloadSystems();
    void SortRenderables();
};


#endif //CMAKESFMLPROJECT_SYSTEMSHANDLER_H
