#pragma once
#include <cstddef>

bool GenerateSecurityKey(
    const unsigned char* seed,
    unsigned int seedSize,
    unsigned char* key,
    unsigned int keyCapacity,
    unsigned int& outputSize
);
