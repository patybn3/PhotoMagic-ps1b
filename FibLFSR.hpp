/*
    Copyright 2023 Patricia Antlitz
*/
#pragma once
#include <iostream>
#include <string>
#include <vector>

class FibLFSR {
 public:
    // Constructor to create LFSR with the given initial seed
    explicit FibLFSR(std::string seed);
    // Simulate one step and return the new bit as 0 or 1
    int step();
    int stepColor();
    // Simulate k steps and return a k-bit integer
    int generate(int k);

    friend std::ostream& operator<<(std::ostream& out, const FibLFSR& lfsr);

 private:
    std::string setRegister;
};

