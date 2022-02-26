/*  thic source file contains functions that generate pseudorandom
    numbers through a Linear congruent generator */
#include <pic32mx.h>

// defining parameters for LCG
#define m (1 << 31)
#define a 1103515245
#define c 12345

// Initializing seed value
int seed = 345197; 

// Function that returns absolute value of an integer
int abs (int val){
    int tmp = val >> 31; //ffffffff or 00000000
    val = val ^ tmp; 
    val = val + (tmp & 1);
    return val;
}


/**
    function that returns a pseudorandom number in a range. 
    if range = N will return a number between [0,(N - 1)].
    Function utilizes a Linear congruent generator to generate 
    pseudorandom numbers.
*/
int random_number (int range){
    seed = (a*seed + c) % m;
    return abs(seed % range);
}
