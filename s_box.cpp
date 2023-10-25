#include "s_box.h"

SBox::SBox() {
    sbox = generate_sbox(); // генеруємо таблицю констант
    inv_sbox = generate_inv_sbox(sbox); // генеруємо зворотню таблицю констант
}

uint8_t SBox::affineTransformation(uint8_t value) {
    uint8_t xformed = value;
    for (int i = 0; i < 4; i++) {
        xformed ^= ((value >> i) & 1) ^ ((value >> (i+2)) % 4) ^ ((value >> (i+3)) % 4); // афінне перетворення за аналогією з aes
    }
    return xformed ^ AFFINE_CONSTANT;
}

uint8_t SBox::multiplyBy3(uint8_t value) {
    return value ^ (value << 1) ^ (value & 0x08 ? POLYNOMIAL : 0); // множимо саме на 3 згідно з концепцією генераторів у теорії генераторів
}

std::vector<uint8_t> SBox::generate_sbox() {
    std::vector<uint8_t> sbox(NUM_ELEMENTS, 0);
    unsigned char p = 1, q = 1;

    do {
        p = multiplyBy3(p);
        q ^= q << 1;
        q ^= q << 2;
        q &= 0x0F; // Залишаємо тільки 4 нижніх біта

        sbox[p] = affineTransformation(q);
    } while (p != 1);

    sbox[0] = AFFINE_CONSTANT;
    return sbox;
}

std::vector<uint8_t> SBox::generate_inv_sbox(const std::vector<uint8_t>& sbox) {
    std::vector<uint8_t> inv_sbox(NUM_ELEMENTS, 0);

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        inv_sbox[sbox[i]] = i;
    }
    return inv_sbox;
}

uint8_t SBox::transform(uint8_t input) const {
    uint8_t leftNibble = (input >> 4) & 0x0F;
    uint8_t rightNibble = input & 0x0F;

    leftNibble = sbox[leftNibble];
    rightNibble = sbox[rightNibble];

    return (leftNibble << 4) | rightNibble;
}

uint8_t SBox::inverse_transform(uint8_t input) const {
    uint8_t leftNibble = (input >> 4) & 0x0F;
    uint8_t rightNibble = input & 0x0F;

    leftNibble = inv_sbox[leftNibble];
    rightNibble = inv_sbox[rightNibble];

    return (leftNibble << 4) | rightNibble;
}