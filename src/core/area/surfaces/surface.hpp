#ifndef _SURFACE_HPP_
#define _SURFACE_HPP_

#include <cstdint>

#include "../dust.hpp"
#include <vector>
using std::vector;


class Surface
{
public:
    vector<vector<int16_t>> surface;
    Surface(int16_t size): surface(size, vector<int16_t>(size)){}
};
#endif //_SURFACE_HPP_