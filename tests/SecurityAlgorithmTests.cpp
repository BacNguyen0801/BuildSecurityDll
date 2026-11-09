#include "SecurityAlgorithm.h"
#include <cassert>

int main()
{
    const unsigned char seed[] = {0x00, 0x12, 0x34, 0xFF};
    unsigned char key[sizeof(seed)] = {};
    unsigned int outputSize = 0;

    assert(GenerateSecurityKey(seed, sizeof(seed), key, sizeof(key), outputSize));
    assert(outputSize == sizeof(seed));
    assert(key[0] == 0xAA);
    assert(key[1] == 0xB8);
    assert(key[2] == 0x9E);
    assert(key[3] == 0x55);

    unsigned char tooSmall[2] = {};
    outputSize = 123;
    assert(!GenerateSecurityKey(seed, sizeof(seed), tooSmall, sizeof(tooSmall), outputSize));
    assert(outputSize == 0);
    return 0;
}
