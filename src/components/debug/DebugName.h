//
// Created by Arya Rakha on 6/26/2023.
//

#ifndef ECSTEROID_DEBUGNAME_H
#define ECSTEROID_DEBUGNAME_H

#include <string>
#include <entt/entt.hpp>

struct DebugName {
public:
    std::string name;

    static std::string Get(entt::registry* registry, entt::entity entity){
        auto debugName = registry->try_get<DebugName>(entity);
        if (debugName != nullptr) return debugName->name;
        else return "ID#"+ std::to_string(static_cast<std::uint32_t>(entity));
    }
};


#endif //ECSTEROID_DEBUGNAME_H
