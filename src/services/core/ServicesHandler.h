//
// Created by Arya Rakha on 7/27/2023.
//

#ifndef ECSTEROID_SERVICESHANDLER_H
#define ECSTEROID_SERVICESHANDLER_H


#include <map>
#include <typeinfo>
#include <memory>
#include <vector>
#include <stdexcept>
#include "ILocatableService.h"
#include "ILoadableService.h"
#include "IUpdatableService.h"

class ServicesHandler {
private:
    std::map<const std::type_info*, const std::shared_ptr<ILocatableService>> locatableServices;
    std::vector<std::shared_ptr<ILoadableService>> loadableServices;
    std::vector<std::shared_ptr<IUpdatableService>> updatableServices;



public:
    template <typename T>
    void Register(T* service){
        std::shared_ptr<T> servicePtr(service);

        if constexpr (std::is_base_of_v<ILocatableService, T>)
            locatableServices.emplace(&typeid(T), servicePtr);

        if constexpr (std::is_base_of_v<ILoadableService, T>) loadableServices.push_back(servicePtr);
        if constexpr (std::is_base_of_v<IUpdatableService, T>) updatableServices.push_back(servicePtr);
    }

    template <typename T>
    std::shared_ptr<T> Locate(){
        static_assert(std::is_base_of_v<ILocatableService, T>, "T must be derived from ILocatableService");
        auto it = locatableServices.find(&typeid(T));
        if (it != locatableServices.end()) return std::static_pointer_cast<T>(it->second);

        std::string name = typeid(T).name();
        throw std::invalid_argument("Trying to Locate Service but could not find " + name);
    }

    void Load();
    void Unload();
    void Update(float deltaTime);
};


#endif //ECSTEROID_SERVICESHANDLER_H
