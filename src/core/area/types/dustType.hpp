#ifndef _DUSTTYPE_HPP_
#define _DUSTTYPE_HPP_

#define DUST_TYPE_AIR 0
#define DUST_TYPE_DIRT 1

class _DustType {
public:
    uint16_t type;
    unsigned short int size;
    void *texture;
};


#endif 