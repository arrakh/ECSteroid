//
// Created by Arya Rakha on 6/10/2023.
//

#ifndef CMAKESFMLPROJECT_SFMLDRAWABLE_H
#define CMAKESFMLPROJECT_SFMLDRAWABLE_H

#include <SFML/Graphics.hpp>
#include <memory>

class SFMLDrawable {
public:
    int order = 0;
    std::shared_ptr<sf::Drawable> drawable;
};


#endif //CMAKESFMLPROJECT_SFMLDRAWABLE_H
