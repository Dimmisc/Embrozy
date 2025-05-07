#ifndef _DUSTTYPE_HPP_
#define _DUSTTYPE_HPP_


#define DUST_SIZE_STANDART 2
#define DUST_SIZE_SMALL 1 // Use small size for very efficient computer
#define DUST_SIZE_BIG 4 // Use big size for not efficient computer
#define DUST_SIZE_CHECK 8 // Using in debugging and testing features

class _DustType {
public:
    int type;
    unsigned short int size;
    void *texture;
};


#endif 