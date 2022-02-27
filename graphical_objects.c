#include <stdint.h>
#include "graphical_objects.h"
#include "game_header.h"

void obst1_procedure();

// Player pixel coordinates
uint8_t player[32][2] = {{11,2},{12,2},{17,2},{18,2},{12,3},
{13,3},{16,3},{17,3},{13,4},{14,4},
{15,4},{16,4},{13,5},{15,5},{12,6},
{16,6},{12,7},{16,7},{11,8},{17,8},
{11,9},{17,9},{11,10},{13,10},{17,10},
{12,11},{16,11},{12,12},{16,12},{13,13},
{15,13},{14,14}};

// Collision sensor pixel coordinates
// are a few vital coordinates on player which is used to collision check
uint8_t collision_sensors[9][2] = {{11,2},{18,2},{12,6},{16,6},{11,10},
{17,10},{12,12},{16,12},{14,14}};

/** Below are non-live obstacle, these what any newly generated live
 *  obstacle are initialized as
**/

uint8_t obst0[30][2] = {{30,129},{31,129},{27,130},{28,130},{29,130},
{24,131},{25,131},{26,131},{21,132},{22,132},
{23,132},{18,133},{19,133},{20,133},{16,134},
{17,134},{18,135},{19,135},{20,135},{21,136},
{22,136},{23,136},{24,137},{25,137},{26,137},
{27,138},{28,138},{29,138},{30,139},{31,139}
};

uint8_t obst1[51][2] = {{0,130},{1,130},{2,130},{3,130},{4,130},
{20,130},{21,130},{22,130},{23,130},{24,130},
{25,130},{26,130},{27,130},{28,130},{29,130},
{30,130},{31,130},{4,131},{5,131},{19,131},
{21,131},{5,132},{18,132},{22,132},{5,133},
{18,133},{22,133},{5,134},{18,134},{22,134},
{4,135},{5,135},{19,135},{21,135},{0,136},
{1,136},{2,136},{3,136},{4,136},{20,136},
{21,136},{22,136},{23,136},{24,136},{25,136},
{26,136},{27,136},{28,136},{29,136},{30,136},
{31,136}};

uint8_t obst1lower[80][2] = {{29,129},{30,129},{31,129},{32,129},{33,129},
{34,129},{35,129},{36,129},{37,129},{38,129},
{39,129},{40,129},{41,129},{42,129},{43,129},
{44,129},{45,129},{46,129},{47,129},{48,129},
{49,129},{50,129},{51,129},{52,129},{53,129},
{54,129},{55,129},{56,129},{57,129},{58,129},
{59,129},{60,129},{61,129},{62,129},{63,129},
{28,130},{30,130},{27,131},{31,131},{27,132},
{31,132},{27,133},{31,133},{28,134},{30,134},
{29,135},{30,135},{31,135},{32,135},{33,135},
{34,135},{35,135},{36,135},{37,135},{38,135},
{39,135},{40,135},{41,135},{42,135},{43,135},
{44,135},{45,135},{46,135},{47,135},{48,135},
{49,135},{50,135},{51,135},{52,135},{53,135},
{54,135},{55,135},{56,135},{57,135},{58,135},
{59,135},{60,135},{61,135},{62,135},{63,135}
};


uint8_t obst1upper[65][2] =
{{0,129},{1,129},{2,129},{3,129},{4,129},
{5,129},{6,129},{7,129},{8,129},{9,129},
{10,129},{11,129},{12,129},{13,129},{14,129},
{15,129},{16,129},{17,129},{18,129},{19,129},
{20,129},{21,129},{22,129},{23,129},{24,129},
{25,129},{26,129},{27,129},{28,129},{29,129},
{30,130},{31,131},{31,132},{31,133},{30,134},
{0,135},{1,135},{2,135},{3,135},{4,135},
{5,135},{6,135},{7,135},{8,135},{9,135},
{10,135},{11,135},{12,135},{13,135},{14,135},
{15,135},{16,135},{17,135},{18,135},{19,135},
{20,135},{21,135},{22,135},{23,135},{24,135},
{25,135},{26,135},{27,135},{28,135},{29,135}
};



// Array pointer to collision sensor
uint8_t (*coll_p) [9][2] = &collision_sensors;

// Array pointer to array of live 2d objects
uint8_t live_objects[3][LIVE_SIZE][2];
uint8_t (*live_objects_pointer)[3][LIVE_SIZE][2] = &live_objects;

/**
 * @brief copies a non-live obstacle and puts it in live objects array
 * 
 * @param k index on live objects array to put in
 * @param rows number of (x,y) pixel coordinates of obstacle
 * @param obst_pointer points to array of pixel coordinates for the obstacle
 */
void put_obstacle_in_live (int k, int rows, uint8_t *obst_pointer){
    int cols = 2;
    int i,j;
    j = 0;
    for (i = 0; i < rows; i++){
        if (*(obst_pointer + i*cols) == 253) continue;
        (*live_objects_pointer)[k][j][0] = *(obst_pointer + i*cols);
        (*live_objects_pointer)[k][j][1] = *(obst_pointer + i*cols + 1);
        j++;
    }
    
}

/**
 * @brief Randomly picks an obstacle type to go live
 * 
 */
void generate_obstacle (){
    int type = random_number(2);
    int i;
    uint8_t steps;
    uint8_t temparr[65][2];
    
    switch (type)
    {
    case 0:
    /*
        steps = 15;

        int temparr[65][2];
        
        for (i = 0; i < 65; i++){
            if ((uint8_t)(obst1upper[i][0] - steps) <= ENDOF && (uint8_t) (obst1upper[i][0] - steps) > 31){
                obst1upper[i][0] = 253;
                obst1upper[i][1] = 253;
            }
            else {
                obst1upper[i][0] -= steps;
            }
        }
        
        put_obstacle_in_live(0, 65, obst1upper[0]);
        */
        obst1_procedure();
        break;
    case 1:
        obst1_procedure();
        //moveObjectPixels (0,5,UP);
        break;
    default:
        break;
    }
}

/**
 * @brief removes an obstacle from the live objects array
 * 
 * @param index index at which the obstacle is in
 */
void disassemble_obstacle (int index){
    int i, j;
    int k = index;
    for (i = 0; i < LIVE_SIZE; i++){
        for (j = 0; j < 2; j++){
            if ((*live_objects_pointer)[k][i][j] == ENDOF) break;
            (*live_objects_pointer)[k][i][j] = ENDOF;
        }
    }
    generate_obstacle();
}

/**
 * @brief collision check between obstacles and collision sensor
 * 
 * @return int returns 1 if collision detected, else 0
 */
int collision_check (){
    int flag;
    int i, k;
    for (k = 0; k < 3; k++){
        i = 0;
        while((*live_objects_pointer)[k][i][0] != ENDOF && i < LIVE_SIZE){
            flag = collision_by_pixels ((*live_objects_pointer)[k][i][0], (*live_objects_pointer)[k][i][1]);
            if (flag) return 1;
            i++;
        }
    }
    return 0;
}


int collision_by_pixels (int arr_row, int arr_col){
    int i;
    for (i = 0; i < 9; i++){
        if ((arr_row == (*coll_p)[i][0]) && (arr_col == (*coll_p)[i][1])){
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Initializes the live object array
 * every index is set to ENDOF
 * ENDOF signifies end of array, so that array is not read past ENDOF
 * 
 */
void init_live (){
    int i, j, k;
    for (k = 0; k < 3; k++){
        for (i = 0; i < LIVE_SIZE; i++){
            for (j = 0; j < 2; j++){
                (*live_objects_pointer)[k][i][j] = ENDOF;
            }
        }
    }
}

uint8_t temparr[145][2];

void obst1_procedure (){
    uint8_t steps_lower = (uint8_t)random_number(10);
    uint8_t height_up = steps_lower + 5;
    uint8_t space_beetween = (uint8_t) random_number_between (10, 16);
    uint8_t height_down = ROWS - space_beetween - height_up;
    uint8_t steps_upper = ROWS - height_down;

    int i, j;
    
    //uint8_t templower[80][2];

    for (i = 0; i < 65; i++){
        temparr[i][0] = obst1upper[i][0];
        temparr[i][1] = obst1upper[i][1];
    }
        
    for (i = 0; i < 65; i++){
        if ((uint8_t)(temparr[i][0] - steps_upper) <= ENDOF && (uint8_t) (temparr[i][0] - steps_upper) > 31){
            temparr[i][0] = 253;
            temparr[i][1] = 253;
        }
        else {
            temparr[i][0] -= steps_upper;
        }
    }

    j = 0;
    for (i = 65; i < 145; i++){
        temparr[i][0] = obst1lower[j][0];
        temparr[i][1] = obst1lower[j][1];
        j++;
    }
    for (i = 65; i < 145; i++){
        temparr[i][0] -= steps_lower;
    }
    for (i = 65; i < 145; i++){
        if ((uint8_t)(temparr[i][0]) <= ENDOF && (uint8_t) (temparr[i][0]) > 31){
            temparr[i][0] = 253;
            temparr[i][1] = 253;
        }
    }
    
    put_obstacle_in_live(0,145, temparr[0]);
    //put_obstacle_in_live(1,80, templower[0]);
}

