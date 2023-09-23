//
// Created by Arya Rakha on 9/24/2023.
//

#ifndef ECSTEROID_RELATION_H
#define ECSTEROID_RELATION_H


#include <cstdlib>
#include "entt/entity/entity.hpp"

struct Relation {
    std::size_t children {};
    entt::entity first {entt::null};
    entt::entity prev {entt::null};
    entt::entity next {entt::null};
    entt::entity parent {entt::null};
};


#endif //ECSTEROID_RELATION_H
