//
// Created by Arya Rakha on 6/10/2023.
//

#ifndef CMAKESFMLPROJECT_SFMLTRANSFORMABLE_H
#define CMAKESFMLPROJECT_SFMLTRANSFORMABLE_H

#include <SFML/Graphics.hpp>
#include <memory>

class SFMLTransformable {
public:
    std::shared_ptr<sf::Transformable> transformable;
    float offsetAngle = 0.f;
    Vector2 offsetPosition = Vector2(0.f, 0.f);
};


#endif //CMAKESFMLPROJECT_SFMLTRANSFORMABLE_H
