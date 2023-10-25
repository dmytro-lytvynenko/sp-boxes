#pragma once

#include <iostream>
#include <vector>

class SBox {
private:
    const uint8_t POLYNOMIAL = 0x13; // Поліном для GF(2^4): x^4 + x + 1
    const uint8_t AFFINE_CONSTANT = 0x05;
    const uint8_t NUM_ELEMENTS = 16;
    std::vector<uint8_t> sbox;
    std::vector<uint8_t> inv_sbox;

    uint8_t multiplyBy3(uint8_t value);

    uint8_t affineTransformation(uint8_t value);
public:
    SBox();

    std::vector<uint8_t> generate_sbox();
    std::vector<uint8_t> generate_inv_sbox(const std::vector<uint8_t>& sbox);

    uint8_t transform(uint8_t input) const;
    uint8_t inverse_transform(uint8_t input) const;
};
