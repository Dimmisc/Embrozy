#include "world-gen.hpp"

Generator Init_PCG(int seed) {
    Generator gen;
    // Now Creating general_generator
    FastNoiseLite world_noise;
    world_noise.SetSeed(seed);
    world_noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    world_noise.SetFrequency(0.00003f);

    world_noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    world_noise.SetFractalOctaves(9);        
    world_noise.SetFractalLacunarity(5.5f);  
    world_noise.SetFractalGain(0.222f);   

    gen.world_generator = world_noise;
    return gen;
}