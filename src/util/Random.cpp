//
// Created by Arya Rakha on 8/2/2023.
//

#include "Random.h"

std::random_device Random::dev;
std::mt19937 Random::rng{dev()};