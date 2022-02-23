#include <pic32mx.h>

#define m (1 << 31)
#define a 1103515245
#define c 12345

int seed = 345197;

int abs (int val){
    return val >> 31? -1 * val: val;
}

int random_number (int range){
    seed = (a*seed + c) % m;
    return abs(seed % range);
}
