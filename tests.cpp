#include <iostream>
#include "s_box.h"
#include "p_box.h"

void testSBox() {
    SBox sbox;

    for (uint16_t input = 0; input < 256; input++) {
        uint16_t transformed = sbox.transform(input);
        uint16_t inv_transformed = sbox.inverse_transform(transformed);

        if (input != inv_transformed) {
            std::cerr << "SBox Test Failed: " << static_cast<int>(input) << " != " << inv_transformed << std::endl;
        }
        else {
            std::cout << "SBox Test Passed: " << input << " == " << inv_transformed << std::endl;
        }
    }
}

void testPBox() {
    for (uint16_t input = 0; input < 256; input++) {
        uint16_t transformed = PBox::transform(input);
        uint16_t inv_transformed = PBox::inverse_transform(transformed);

        if (input != inv_transformed) {
            std::cerr << "PBox Test Failed: " << input << " != " << inv_transformed << std::endl;
        }
        else {
            std::cout << "PBox Test Passed: " << input << " == " << inv_transformed << std::endl;
        }
    }
}

int main() {
    testSBox();
    testPBox();

    return 0;
}