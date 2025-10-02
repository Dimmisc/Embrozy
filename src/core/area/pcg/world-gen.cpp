#include "world-gen.hpp"

FastNoiseLite *Init_PCG(int seed) {
    FastNoiseLite noise;
    noise.SetSeed(seed);
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFrequency(0.04f);

    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(5);        
    noise.SetFractalLacunarity(2.0f);  
    noise.SetFractalGain(0.5f);        
    return &noise;
}