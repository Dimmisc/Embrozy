#ifndef WORLD_GEN_HPP_
#define WORLD_GEN_HPP_
#include "../cell.hpp"
#include <FastNoiseLite.h>

FastNoiseLite *Init_PCG(int seed);

Cell *GenerateCellVAO(CellPos Position);
#endif // WORLD_GEN_HPP