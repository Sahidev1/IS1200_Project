#include <stdint.h>
#include "graphical_objects.h"
#include "game_header.h"


uint8_t player[32][2] = {{11,2},{12,2},{17,2},{18,2},{12,3},
{13,3},{16,3},{17,3},{13,4},{14,4},
{15,4},{16,4},{13,5},{15,5},{12,6},
{16,6},{12,7},{16,7},{11,8},{17,8},
{11,9},{17,9},{11,10},{13,10},{17,10},
{12,11},{16,11},{12,12},{16,12},{13,13},
{15,13},{14,14}};

uint8_t collision_sensors[9][2] = {{11,2},{18,2},{12,6},{16,6},{11,10},
{17,10},{12,12},{16,12},{14,14}};

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

uint8_t (*coll_p) [9][2] = &collision_sensors;

uint8_t (*obst1p) [51][2] = &obst1;

uint8_t live_objects[3][100][2];
uint8_t (*live_objects_pointer)[3][100][2] = &live_objects;
//uint8_t (*livep0)[100][2] = &live_objects[0];

//uint8_t (*obst1_livep)[51][2] = &obst1_live;

void put_obstacle_in_live (int k, int rows, uint8_t *obst_pointer){
    int cols = 2;
    int i,j;
    for (i = 0; i < rows; i++){
        (*live_objects_pointer)[k][i][0] = *(obst_pointer + i*cols);
        (*live_objects_pointer)[k][i][1] = *(obst_pointer + i*cols + 1);
    }
    
}

void generate_obstacle (){
    int type = random_number(2);
    switch (type)
    {
    case 0:
        put_obstacle_in_live(0, 30, obst0[0]);
        break;
    case 1:
        put_obstacle_in_live(0, 51, obst1[0]);
        break;
    default:
        break;
    }
}


void disassemble_obstacle (int index){
    int i, j;
    int k = index;
    for (i = 0; i < 100; i++){
        for (j = 0; j < 2; j++){
            if ((*live_objects_pointer)[k][i][j] == ENDOF) break;
            (*live_objects_pointer)[k][i][j] = ENDOF;
        }
    }
    generate_obstacle();
}


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

void init_live (){
    int i, j, k;
    for (k = 0; k < 3; k++){
        for (i = 0; i < 100; i++){
            for (j = 0; j < 2; j++){
                (*live_objects_pointer)[k][i][j] = ENDOF;
            }
        }
    }
}

/*
void reset_obst(){
    int i, j;
    for (i = 0; i < 51; i++){
        for (j = 0; j < 2; j++){
            (*obst1_livep)[i][j] = (*obst1p)[i][j];
        }
    }
}*/


