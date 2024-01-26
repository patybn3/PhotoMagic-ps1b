/*
    Copyright 2023 Patricia Antlitz
*/
#include "PhotoMagic.hpp"
#include <iostream>
#include <random>

namespace PhotoMagic {
    void transform(sf::Image& img, FibLFSR* seed) {
        unsigned int width = img.getSize().x;
        unsigned int height = img.getSize().y;

        for (unsigned int y = 0; y < height; ++y) {
            for (unsigned int x = 0; x < width; ++x) {
                sf::Color pixel = img.getPixel(x, y);
                // true = this is an image
                uint8_t red = seed->stepColor();
                uint8_t green = seed->stepColor();
                uint8_t blue = seed->stepColor();

                pixel.r ^= red;
                pixel.g ^= green;
                pixel.b ^= blue;

                img.setPixel(x, y, pixel);
            }
        }
    }
}  // namespace PhotoMagic
