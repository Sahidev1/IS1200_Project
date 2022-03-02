#include <stdint.h>
#include "graphical_objects.h"
#include "game_header.h"

void obst0_procedure();
void obst1_procedure();
void obst2_procedure ();

uint8_t frame[316][2] = {{0,0},{1,0},{2,0},{3,0},{4,0},
{5,0},{6,0},{7,0},{8,0},{9,0},
{10,0},{11,0},{12,0},{13,0},{14,0},
{15,0},{16,0},{17,0},{18,0},{19,0},
{20,0},{21,0},{22,0},{23,0},{24,0},
{25,0},{26,0},{27,0},{28,0},{29,0},
{30,0},{31,0},{0,1},{31,1},{0,2},
{31,2},{0,3},{31,3},{0,4},{31,4},
{0,5},{31,5},{0,6},{31,6},{0,7},
{31,7},{0,8},{31,8},{0,9},{31,9},
{0,10},{31,10},{0,11},{31,11},{0,12},
{31,12},{0,13},{31,13},{0,14},{31,14},
{0,15},{31,15},{0,16},{31,16},{0,17},
{31,17},{0,18},{31,18},{0,19},{31,19},
{0,20},{31,20},{0,21},{31,21},{0,22},
{31,22},{0,23},{31,23},{0,24},{31,24},
{0,25},{31,25},{0,26},{31,26},{0,27},
{31,27},{0,28},{31,28},{0,29},{31,29},
{0,30},{31,30},{0,31},{31,31},{0,32},
{31,32},{0,33},{31,33},{0,34},{31,34},
{0,35},{31,35},{0,36},{31,36},{0,37},
{31,37},{0,38},{31,38},{0,39},{31,39},
{0,40},{31,40},{0,41},{31,41},{0,42},
{31,42},{0,43},{31,43},{0,44},{31,44},
{0,45},{31,45},{0,46},{31,46},{0,47},
{31,47},{0,48},{31,48},{0,49},{31,49},
{0,50},{31,50},{0,51},{31,51},{0,52},
{31,52},{0,53},{31,53},{0,54},{31,54},
{0,55},{31,55},{0,56},{31,56},{0,57},
{31,57},{0,58},{31,58},{0,59},{31,59},
{0,60},{31,60},{0,61},{31,61},{0,62},
{31,62},{0,63},{31,63},{0,64},{31,64},
{0,65},{31,65},{0,66},{31,66},{0,67},
{31,67},{0,68},{31,68},{0,69},{31,69},
{0,70},{31,70},{0,71},{31,71},{0,72},
{31,72},{0,73},{31,73},{0,74},{31,74},
{0,75},{31,75},{0,76},{31,76},{0,77},
{31,77},{0,78},{31,78},{0,79},{31,79},
{0,80},{31,80},{0,81},{31,81},{0,82},
{31,82},{0,83},{31,83},{0,84},{31,84},
{0,85},{31,85},{0,86},{31,86},{0,87},
{31,87},{0,88},{31,88},{0,89},{31,89},
{0,90},{31,90},{0,91},{31,91},{0,92},
{31,92},{0,93},{31,93},{0,94},{31,94},
{0,95},{31,95},{0,96},{31,96},{0,97},
{31,97},{0,98},{31,98},{0,99},{31,99},
{0,100},{31,100},{0,101},{31,101},{0,102},
{31,102},{0,103},{31,103},{0,104},{31,104},
{0,105},{31,105},{0,106},{31,106},{0,107},
{31,107},{0,108},{31,108},{0,109},{31,109},
{0,110},{31,110},{0,111},{31,111},{0,112},
{31,112},{0,113},{31,113},{0,114},{31,114},
{0,115},{31,115},{0,116},{31,116},{0,117},
{31,117},{0,118},{31,118},{0,119},{31,119},
{0,120},{31,120},{0,121},{31,121},{0,122},
{31,122},{0,123},{31,123},{0,124},{31,124},
{0,125},{31,125},{0,126},{31,126},{0,127},
{1,127},{2,127},{3,127},{4,127},{5,127},
{6,127},{7,127},{8,127},{9,127},{10,127},
{11,127},{12,127},{13,127},{14,127},{15,127},
{16,127},{17,127},{18,127},{19,127},{20,127},
{21,127},{22,127},{23,127},{24,127},{25,127},
{26,127},{27,127},{28,127},{29,127},{30,127},
{31,127}};


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

uint8_t obst0[47][2] = {{23,131},{27,131},{22,132},{24,132},{26,132},
{28,132},{21,133},{25,133},{29,133},{20,134},
{29,134},{20,135},{23,135},{29,135},{19,136},
{29,136},{19,137},{28,137},{19,138},{20,138},
{28,138},{20,139},{27,139},{20,140},{27,140},
{21,141},{26,141},{22,142},{24,142},{25,142},
{21,143},{25,143},{20,144},{26,144},{19,145},
{22,145},{23,145},{27,145},{19,146},{21,146},
{24,146},{27,146},{19,147},{20,147},{25,147},
{26,147},{27,147}};


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

uint8_t obst2[20][2] = {{24,129},{25,129},{26,129},{27,129},{28,129},
{29,129},{30,129},{24,130},{30,130},{24,131},
{30,131},{24,132},{30,132},{24,133},{25,133},
{26,133},{27,133},{28,133},{29,133},{30,133}
};

// Array pointer to collision sensor
uint8_t (*coll_p) [9][2] = &collision_sensors;

// Array pointer to array of live 2d objects
uint8_t live_obstacles[3][LIVE_SIZE][2];
uint8_t (*live_obstacles_pointer)[3][LIVE_SIZE][2] = &live_obstacles;

obstData obst_data;
obstacle0_state obstacle0_status;
void init_structs (){
    int i;
    for (i = 0; i < 3; i++){
        obst_data.filled_array_indexes[i] = EMPTY;
        obst_data.obstacle_type_at_array_indexes[i] = -1;
        obst_data.obst2_limit_value[i] = -1;
        obst_data.obst0_limit_value[i] = -1;
    }
}

int is_there_obstX_live(int obstnr){
    int* is_filled_p = obst_data.filled_array_indexes;
    int* type_p = obst_data.obstacle_type_at_array_indexes;
    int i;
    for (i = 0; i < MAX_LIVE_OBST; i++){
        if (*(is_filled_p + i) == FILLED){
            if (*(type_p + i) == obstnr){
                return 1;
            }
        }
    }
    return 0;
}

void update_limit_obstX (int obstnr, int index, int limit){
    if (obstnr == 2){
        obst_data.obst2_limit_value[index] = limit;
    }
    if (obstnr == 0){
        obst_data.obst0_limit_value[index] = limit;
    }
}

int get_limit_of_obstX (int obstnr, int index){
    if (obstnr == 2){
        return obst_data.obst2_limit_value[index];
    }
    return obst_data.obst0_limit_value[index];
}

int index_of_obst0 (){
    int* is_filled_p = obst_data.filled_array_indexes;
    int* type_p = obst_data.obstacle_type_at_array_indexes;
    int i;
    if (is_there_obstX_live(0)){
        for (i = 0; i < MAX_LIVE_OBST; i++){
            if (*(is_filled_p + i) && *(type_p + i) == 0){
                return i;
            }
        }
    }
    return -1;
}

void move_up_down_obstX (int obstnr){
    int limit_status;
    int* is_filled_p = obst_data.filled_array_indexes;
    int* type_p = obst_data.obstacle_type_at_array_indexes;
    int i;
    for (i = 0; i < MAX_LIVE_OBST; i++){
        if (*(is_filled_p + i) == FILLED && *(type_p + i) == obstnr){
            if (obstnr == 2){
                limit_status = obst_data.obst2_limit_value[i];
            }
            if (obstnr == 0){
                limit_status = obst_data.obst0_limit_value[i];
            }
            if (limit_status == 1){
                moveObjectPixels(i, 1, DOWN);
                
            }
            else {
                moveObjectPixels(i, 1, UP);
            }
        }
    }
}

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
        if (*(obst_pointer + i*cols) == ROW_COORD_OUT_OF_BOUNDS) continue;
        (*live_obstacles_pointer)[k][j][0] = *(obst_pointer + i*cols);
        (*live_obstacles_pointer)[k][j][1] = *(obst_pointer + i*cols + 1);
        j++;
    }
}

int getFreeIndex (){
    int* array_p = &obst_data.filled_array_indexes[0];
    int i;
    for (i = 0; i < MAX_LIVE_OBST; i++){
        if (*(array_p + i) == EMPTY){
            *(array_p + i) = FILLED;
            return i;
        }
    }
    return -1;
}

void freeIndex (int index){
    obst_data.filled_array_indexes[index] = EMPTY;
    obst_data.obstacle_type_at_array_indexes[index] = -1;
}

/**
 * @brief Randomly picks an obstacle type to go live
 * 
 */
void generate_obstacle (){
    int type;
    if (is_there_obstX_live(0)){
        type = obstacle_gen_rand(2) + 1;
    }
    else {
        type = obstacle_gen_rand(MAX_LIVE_OBST);
    }
    int i,k;
    switch (type)
    {
    case 0:
        k = getFreeIndex();
        if (k != -1){
            obst0_procedure(k);
            
            obst_data.obstacle_type_at_array_indexes[k] = 0;
        }
        break;
    case 1:
        k = getFreeIndex();
        if (k != -1){
            obst1_procedure(k);
            
            obst_data.obstacle_type_at_array_indexes[k] = 1;
        }
        break;
    case 2:
        k = getFreeIndex();
        if (k != -1){
            obst2_procedure(k);
            obst_data.obstacle_type_at_array_indexes[k] = 2;
        }
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
            if ((*live_obstacles_pointer)[k][i][j] == ENDOF) break;
            (*live_obstacles_pointer)[k][i][j] = ENDOF;
        }
    }
    freeIndex(index);
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
        while((*live_obstacles_pointer)[k][i][0] != ENDOF && i < LIVE_SIZE){
            flag = collision_by_pixels ((*live_obstacles_pointer)[k][i][0], (*live_obstacles_pointer)[k][i][1]);
            if (flag) return 1;
            i++;
        }
    }
    return 0;
}

/**
 * @brief checks wheter coordinate from obstacle pixel array 
 * collides with sensor pixel coordinates
 * 
 * @param row_coord row coordinate on OLED
 * @param col_coord column coordinate on OLED
 * @return int , 0 for false, 1 for true
 */
int collision_by_pixels (int row_coord, int col_coord){
    int i;
    for (i = 0; i < 9; i++){
        if ((row_coord == (*coll_p)[i][0]) && (col_coord == (*coll_p)[i][1])){
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
                (*live_obstacles_pointer)[k][i][j] = ENDOF;
            }
        }
    }
}


/**
 * @brief Procedure for combining obst1lower and obst1upper into
 * one cohesive obstacle on the live objects array
 * 
 * The obstacles properties are randomly generated, such as the
 * length of its upper and lowers part, as well as the spacing between 
 * the two parts is randomly generated
 */
void obst1_procedure (int live_obst_index){
    int obst1upper_size = 65;
    int obst1lower_size = 80;
    int combined_size = 145;

    uint8_t temparr[combined_size][2];
    uint8_t steps_lower = (uint8_t)random_number(10);
    uint8_t height_up = steps_lower + 6;
    uint8_t space_beetween = (uint8_t) random_number_between (10, 14);
    uint8_t height_down = ROWS - space_beetween - height_up;
    uint8_t steps_upper = ROWS - height_down;

    int i, j;
    for (i = 0; i < obst1upper_size; i++){
        temparr[i][0] = obst1upper[i][0];
        temparr[i][1] = obst1upper[i][1];
    }
        
    for (i = 0; i < obst1upper_size; i++){
        if ((uint8_t)(temparr[i][0] - steps_upper) <= ENDOF && (uint8_t) (temparr[i][0] - steps_upper) > 31){
            temparr[i][0] = ROW_COORD_OUT_OF_BOUNDS;
            temparr[i][1] = ROW_COORD_OUT_OF_BOUNDS;
        }
        else {
            temparr[i][0] -= steps_upper;
        }
    }

    j = 0;
    for (i = obst1upper_size; i < combined_size; i++){
        temparr[i][0] = obst1lower[j][0];
        temparr[i][1] = obst1lower[j][1];
        j++;
    }
    for (i = obst1upper_size; i < combined_size; i++){
        temparr[i][0] -= steps_lower;
    }
    for (i = obst1upper_size; i < combined_size; i++){
        if ((uint8_t)(temparr[i][0]) <= ENDOF && (uint8_t) (temparr[i][0]) > 31){
            temparr[i][0] = ROW_COORD_OUT_OF_BOUNDS;
            temparr[i][1] = ROW_COORD_OUT_OF_BOUNDS;
        }
    }
    put_obstacle_in_live(live_obst_index,145, temparr[0]);
}

void obst2_procedure (int live_obst_index){
    uint8_t temparr[80][2];
    int height_increase = random_number(11);
    //random_number(3);
    int nr_elements = 20;
    int i,j,k;

    k = 0;
    for (i = 0; i < 20; i++){
       if (obst2[i][0] == 24 && (obst2[i][1] >= 130 && obst2[i][1] <= 132)){
           nr_elements--;
            continue;
       }
        temparr[k][0] = obst2[i][0];
        temparr[k++][1] = obst2[i][1];
    }
 
    int row = 23;
    int col1 = 129;
    int col2 = 133;
    while (height_increase > 0){
        temparr[k][0] = row;
        temparr[k++][1] = col1;
        temparr[k][0] = row--;
        temparr[k++][1] = col2;
        height_increase--;
        nr_elements += 2;
    }
    row++;

    for (j = col1 + 1; j < col2; j++){
        temparr[k][0] = row;
        temparr[k++][1] = j;
        nr_elements++;
    }
    
    obst_data.obst2_limit_value[live_obst_index] = 5; //arbitrary value
    put_obstacle_in_live(live_obst_index, nr_elements, temparr[0]);
}

void obst0_procedure (int live_obst_index){
    obstacle0_status.boost_enabled = false;
    obstacle0_status.boosted_once = false;
    obstacle0_status.boost_enable_steps = random_number_between (20, 50);
    obstacle0_status.boost_disable_steps = random_number_between (25, 75);
    obstacle0_status.timer_boost_enabled = random_number_between (15, 50);
    //set_obst0_boost_delay(obstacle0_status.timer_boost_enabled);
    obstacle0_status.iterator = 0;

    put_obstacle_in_live(live_obst_index, 47, obst0[0]);
}
