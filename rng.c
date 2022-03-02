/*  thic source file contains functions that generate pseudorandom
    numbers through a Linear congruent generator */
#include <pic32mx.h>

// defining parameters for LCG
#define m (1 << 31)
#define a 1103515245
#define c 12345

// Initializing seed value
int seed = 345197; 
int obstacle_gen_seed = 1719021017;

// Function that returns absolute value of an integer
int abs (int val){
    int tmp = val >> 31; //ffffffff or 00000000
    val = val ^ tmp; 
    val = val + (tmp & 1);
    return val;
}

int obstacle_gen_rand (int range){
    obstacle_gen_seed = (a*obstacle_gen_seed + c) % m;
    return abs (obstacle_gen_seed % range);
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

/**
 * @brief returns pseudorandom number between [lower, upper]
 * 
 * @param lower lower range
 * @param upper upper range
 * @return int 
 */
int random_number_between (int lower, int upper){
    seed = (a*seed + c) % m;
    upper++;
    int mod = upper - lower;
    return abs(seed % mod) + lower;
}
