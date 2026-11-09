#include "SecurityAlgorithm.h"

/*
 * NON-SECURE PLACEHOLDER ONLY.
 *
 * Replace this demonstration transform with your authorized OEM algorithm.
 * This XOR example is deliberately not a real Seed & Key implementation.
 */
bool GenerateSecurityKey(
    const unsigned char* seed,
    unsigned int seedSize,
    unsigned char* key,
    unsigned int keyCapacity,
    unsigned int& outputSize)
{
    outputSize = 0;

    if (seed == nullptr || key == nullptr || keyCapacity < seedSize)
        return false;

    for (unsigned int i = 0; i < seedSize; ++i)
        key[i] = static_cast<unsigned char>(seed[i] ^ 0xAAu);

    outputSize = seedSize;
    return true;
}
