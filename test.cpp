// Copyright 2022
// By Dr. Rykalova
// Editted by Dr. Daly
// test.cpp for PS1a
// Edited by Patricia Antlitz, test for PS1a and PS1b 2023
// updated 5/12/2022

#include <iostream>
#include <string>
#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

// this method will compare two images in order to perform some tests
bool compareImages(const sf::Image& img1, const sf::Image& img2) {
  sf::Vector2u size = img1.getSize();

  if (size != img2.getSize()) {
    return false;
  }
  // compare the images by its pixels
  for (unsigned int x = 0; x < size.x; ++x) {
    for (unsigned int y = 0; y < size.y; ++y) {
      sf::Color original = img1.getPixel(x, y);
      sf::Color encrypted = img2.getPixel(x, y);

      if (original.r != encrypted.r || original.g != encrypted.g ||
            original.b != encrypted.b) {
        return false;
      }
    }
  }
  return true;
}

// LFSR tests, bit shifting
BOOST_AUTO_TEST_CASE(testStepInstr1) {
  FibLFSR l("1011011000110110");
  // step(false) boolean value added, passing it as false means its not an image
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
}

// cases when the see is smaller or repetitive
BOOST_AUTO_TEST_CASE(testEdgeCasesStep) {
  FibLFSR seedOnes("11111111");
  FibLFSR seedZeros("00000000");
  FibLFSR seedAlt("01010101");

  BOOST_REQUIRE_EQUAL(seedOnes.step(), 0);
  BOOST_REQUIRE_EQUAL(seedOnes.step(), 0);
  BOOST_REQUIRE_EQUAL(seedOnes.step(), 0);
  BOOST_REQUIRE_EQUAL(seedOnes.step(), 1);
  BOOST_REQUIRE_EQUAL(seedOnes.step(), 1);
  BOOST_REQUIRE_EQUAL(seedOnes.step(), 0);

  BOOST_REQUIRE_EQUAL(seedZeros.step(), 0);
  BOOST_REQUIRE_EQUAL(seedZeros.step(), 0);
  BOOST_REQUIRE_EQUAL(seedZeros.step(), 0);
  BOOST_REQUIRE_EQUAL(seedZeros.step(), 0);
  BOOST_REQUIRE_EQUAL(seedZeros.step(), 0);
  BOOST_REQUIRE_EQUAL(seedZeros.step(), 0);

  BOOST_REQUIRE_EQUAL(seedAlt.step(), 0);
  BOOST_REQUIRE_EQUAL(seedAlt.step(), 0);
  BOOST_REQUIRE_EQUAL(seedAlt.step(), 0);
  BOOST_REQUIRE_EQUAL(seedAlt.step(), 0);
  BOOST_REQUIRE_EQUAL(seedAlt.step(), 1);
  BOOST_REQUIRE_EQUAL(seedAlt.step(), 0);
}

// testing generate(int)
BOOST_AUTO_TEST_CASE(testStepInstr2) {
  FibLFSR l2("1011011000110110");
  BOOST_REQUIRE_EQUAL(l2.generate(9), 51);
}

// stress test, does the code work if a lot of bits
// is generated?
BOOST_AUTO_TEST_CASE(stressTest) {
  FibLFSR stressTest("1011011000110110");
  BOOST_CHECK_NO_THROW(stressTest.generate(1000));
}

// performance on clock
BOOST_AUTO_TEST_CASE(testPerformance) {
  // generate a large number of bits
  std::string seed = "1011011000110110";
  FibLFSR flfsr(seed);
  // and measure execution time using the clock
  clock_t start = clock();
  // 1 million bits
  int r = flfsr.generate(1000000);
  clock_t end = clock();

  double elapse = static_cast<double>(end - start) / CLOCKS_PER_SEC;
  std::cout << elapse << std::endl;
  BOOST_CHECK(r != 0);
}

// strings that are not binary numbers
BOOST_AUTO_TEST_CASE(testErrorHandling) {
  BOOST_CHECK_THROW(FibLFSR empty(""), std::invalid_argument);
  BOOST_CHECK_THROW(FibLFSR invalid("AABBCCDDEEFFGGHH"), std::invalid_argument);
}

// ensure program produces consistent outputs
BOOST_AUTO_TEST_CASE(testConsistency) {
  std::string seed = "1011011000110110";
  std::string seqOne;
  std::string seqTwo;

  FibLFSR flfsr(seed);

  // we will generate in two separate runs and reset the seed
  // midway
  for (int i = 0; i < 10; i++) {
    seqOne += std::to_string(flfsr.step());
  }

  flfsr = FibLFSR(seed);

  for (int i = 0; i < 10; i++) {
    seqTwo += std::to_string(flfsr.step());
  }

  BOOST_CHECK_EQUAL(seqOne, seqTwo);
}

// IMAGE TESTING
// test encryption and decryption
BOOST_AUTO_TEST_CASE(genEncryptionDecryption) {
  FibLFSR fib("1011011000110110");
  sf::Image newImage;

  sf::Image encrypted = newImage;
  // encrypt
  PhotoMagic::transform(encrypted, &fib);
  // decrypt
  PhotoMagic::transform(encrypted, &fib);

  BOOST_CHECK(compareImages(newImage, encrypted));
}

BOOST_AUTO_TEST_CASE(encryptWithDifferentSeeds) {
  FibLFSR fib("1011011000110110");
  FibLFSR fibTwo("0111100100001100");
  sf::Image orgImage;

  sf::Image newImageOne = orgImage;
  sf::Image newImageTwo = orgImage;

  PhotoMagic::transform(newImageOne, &fib);

  PhotoMagic::transform(newImageTwo, &fibTwo);

  BOOST_CHECK(compareImages(newImageOne, newImageTwo));
}

// small image
BOOST_AUTO_TEST_CASE(testSmallImage) {
  FibLFSR fib("1011011000110110");
  sf::Image orgImage;
  // create a 1x1 pixel image to test if the program can handle small images
  orgImage.create(1, 1, sf::Color::White);

  sf::Image encrypted = orgImage;

  PhotoMagic::transform(encrypted, &fib);

  BOOST_CHECK(!compareImages(orgImage, encrypted));
}

// large image
BOOST_AUTO_TEST_CASE(testLargeImage) {
  FibLFSR fib("1011011000110110");
  sf::Image orgImage;
  // create a large pixels image to test if the program can handle it
  orgImage.create(1920, 1920, sf::Color::White);

  sf::Image encrypted = orgImage;

  PhotoMagic::transform(encrypted, &fib);

  BOOST_CHECK(!compareImages(orgImage, encrypted));
}

// Boundary tests:
BOOST_AUTO_TEST_CASE(testSeedsBoundary) {
  // test min seed value
  FibLFSR fibMin("0000000000000001");
  sf::Image orgImageOne;

  sf::Image encryptedOne = orgImageOne;

  PhotoMagic::transform(encryptedOne, &fibMin);

  // test max seed value
  FibLFSR fibMax("1111111111111111");
  sf::Image orgImageTwo;

  sf::Image encryptedTwo = orgImageTwo;

  PhotoMagic::transform(encryptedTwo, &fibMax);

  BOOST_CHECK(compareImages(encryptedOne, encryptedTwo));
}

// test image formats
BOOST_AUTO_TEST_CASE(testFormats) {
  FibLFSR fib("1011011000110110");
  sf::Image orgImageOne;

  // must be a png image
  if (!orgImageOne.loadFromFile("cat.png")) {
    BOOST_FAIL("Incorrect file format. Must be PNG.");
  }

  sf::Image orgImageTwo = orgImageOne;

  sf::Image encryptedOne = orgImageOne;
  PhotoMagic::transform(encryptedOne, &fib);

  sf::Image encryptedTwo = orgImageTwo;
  PhotoMagic::transform(encryptedTwo, &fib);

  BOOST_CHECK(!compareImages(orgImageOne, encryptedOne));
  BOOST_CHECK(!compareImages(orgImageTwo, encryptedTwo));
}
