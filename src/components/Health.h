//
// Created by Arya Rakha on 6/26/2023.
//

#ifndef ECSTEROID_HEALTH_H
#define ECSTEROID_HEALTH_H


class Health {
public:
    float maxHealth;
    float health;

    explicit Health(float health) {
        maxHealth = health;
        this->health = health;
    }
};


#endif //ECSTEROID_HEALTH_H
