#ifndef WORLD_GEN_HPP_
#define WORLD_GEN_HPP_
// #include "../cell.hpp"
#include <FastNoiseLite.h>

// Now having only world generator, 
// later will have more generators
struct Generator {
    // Main world generator
    FastNoiseLite world_generator;
    FastNoiseLite rock_generator;
};

// Function to set up generators,
// that are needed for world generation
Generator *Init_PCG(int seed);

// Function to generate cells model
// Cell *GenerateCellVAO(CellPos Position);

#endif // WORLD_GEN_HPP