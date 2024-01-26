/*
    Copyright 2023 Patricia Antlitz
*/
#pragma once
#include <SFML/Graphics.hpp>

#include "FibLFSR.hpp"

namespace PhotoMagic {
    void transform(sf::Image&, FibLFSR*);
}
