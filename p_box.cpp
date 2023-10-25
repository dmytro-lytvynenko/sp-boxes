#include "p_box.h"

uint8_t PBox::transform(uint8_t input) {
    return (input << 1) | (input >> 7);
}

uint8_t PBox::inverse_transform(uint8_t input) {
    return (input >> 1) | (input << 7);
}