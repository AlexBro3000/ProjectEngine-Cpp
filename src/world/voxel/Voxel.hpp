#pragma once
#include <stdint.h>

class Voxel {
public:
    uint16_t id;

    Voxel() : id(0) {}
    Voxel(uint16_t id) : id(id) {}

};