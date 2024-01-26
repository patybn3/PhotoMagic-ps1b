/*
    Copyright 2023 Patricia Antlitz
*/
#include <iostream>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"

int main(int argc, char const *argv[]) {
    // to show in the terminal
    std::string consoleSeed = "1011011000110110";
    FibLFSR flfsr(consoleSeed);

    for (int i = 0; i < 10; i++) {
        std::cout << flfsr << " " << flfsr.step() << std::endl;
    }

    // reset the seed to run generate()
    flfsr = FibLFSR(consoleSeed);
    std::cout << std::endl;

    for (int i = 0; i < 7; ++i) {
        std::cout << flfsr << " " << flfsr.generate(5) << std::endl;
    }

    // image encryption / decryption
    int xSize = 350;
    int ySize = 250;

    sf::RenderWindow window1(sf::VideoMode(xSize, ySize), "Original");
    sf::RenderWindow window2(sf::VideoMode(xSize, ySize), "Processed");

    if (argc != 4) {
        std::cerr << "Run This Program With The Following Argument Format:\n" << argv[0] <<
            " input_file_name.png output_file_name.png binary_number"
            << std::endl;
        return 1;
    }

    // we will use argv vector
    std::string srcImage = argv[1];
    std::string outImage = argv[2];
    std::string seed = argv[3];

    // The existing image the user will pass as an argument
    sf::Image imageIn;
    if (!imageIn.loadFromFile(srcImage)) {
        std::cerr << "Unable to load the selected image." << std::endl;
        return -1;
    }

    // Putting the image in a sprite in order to be able to use draw()
    sf::Texture getImage;
    getImage.loadFromImage(imageIn);
    sf::Sprite givenImage(getImage);

    // The binary number passed as an argument is passed to the class that performs the LFSR
    FibLFSR generateSeed(seed);

    // from namespace PhotoMagic that encrypts the image using the seed
    PhotoMagic::transform(imageIn, &generateSeed);

    // The image that was encrypted/decrypted is saved in a separate file
    sf::Image newImage;
    newImage.create(imageIn.getSize().x, imageIn.getSize().y);

    for (unsigned int x = 0; x < imageIn.getSize().x; ++x) {
        for (unsigned int y = 0; y < imageIn.getSize().y; ++y) {
            newImage.setPixel(x, y, imageIn.getPixel(x, y));
        }
    }

    if (!newImage.saveToFile(outImage)) {
        std::cerr << "Unable to save the image." << std::endl;
        return -1;
    }

    sf::Texture putImage;
    putImage.loadFromImage(newImage);
    sf::Sprite savedImage(putImage);

    // opening both windows
    while (window1.isOpen() && window2.isOpen()) {
        sf::Event event;

        // Event to close the windows
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window1.close();
        }

        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window2.close();
        }

        // drawing the images to the windows
        window1.clear();
        window1.draw(givenImage);
        window1.display();

        window2.clear();
        window2.draw(savedImage);
        window2.display();
    }
    return 0;
}
