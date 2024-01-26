/*
    Copyright 2023 Patricia Antlitz
*/
#include <iostream>
#include "FibLFSR.hpp"

FibLFSR::FibLFSR(std::string seed) {
    setRegister = seed;
    // this is used to run a test ensuring that the seed is a
    // binary number
    for (char bit : seed) {
        if (bit != '0' && bit != '1') {
            throw std::invalid_argument("Seed must be a binary number");
        }
    }
    if (seed.empty()) {
        throw std::invalid_argument("Seed cannot be empty");
    }
}

int FibLFSR::stepColor() {
    int tPos = (setRegister[0] ^ setRegister[2] ^ setRegister[3] ^ setRegister[5]) - '0';

    // shift the bit, and set a new bit
    char ch = tPos + '0';
    setRegister = setRegister.substr(1) + ch;

    return tPos;
}
// changed from the first version on ps1a
int FibLFSR::step() {
    // step() only performs one step of the lfsr
    /* calculate the tap by performing XOR logic at positions:
    indexes = 0, 2, 3, 5
    */
    int tPos = setRegister[0] ^ setRegister[2] ^ setRegister[3] ^ setRegister[5];

    // shift the bit, and set a new bit
    char ch = tPos + '0';
    setRegister = setRegister.substr(1) + ch;

    return tPos;
}

int FibLFSR::generate(int k) {
    int outputNum = 0;

    for (int i = 0; i < k; i++) {
        // accumulate the bits to yield result
        outputNum = (outputNum << 1) + step();
    }
    return outputNum;
}

std::ostream& operator<<(std::ostream& out, const FibLFSR& lfsr) {
    return out << lfsr.setRegister;
}
