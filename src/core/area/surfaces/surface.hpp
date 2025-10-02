#ifndef _SURFACE_HPP_
#define _SURFACE_HPP_

#include <cstdint>

#include "../dust.hpp"

class Surface
{
public:
    static uint8_t dustSize;
    Dust **dustedSurface;
};
#endif //_SURFACE_HPP_