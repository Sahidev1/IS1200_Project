#include <pic32mx.h>

#define ENDOF 255 // Used for signifying the end of valid values to read in live objects array
#define PIXEL_REACHED_END 254 // Signifies that an obstacles pixel coordinate has reached end of OLED
#define ROW_COORD_OUT_OF_BOUNDS 253 // signifies that pixel coordinate is out of bound ROW range [0,31]
#define LIVE_SIZE 145 // size of live object array
#define MAX_LIVE_OBST 3 // max live obstacles

#define FILLED 1 // used to signify a live obstacle are is non empty
#define EMPTY 0 // used to signify a live obstacle are is empty

typedef enum {false, true} boolean;

/**
 * @brief keeps a check of the current live array
 * obstacles properties
 * 
 */
typedef struct Obstacle_Data {
    int filled_array_indexes[3];
    int obstacle_type_at_array_indexes[3];
    int obst2_limit_value[3];
    int obst0_limit_value[3];
} obstData;

/**
 * @brief keeps a check on properties of any current live
 * obstacle of type 0
 * 
 */
typedef struct Obstacle0_state {
    boolean boost_enabled;
    boolean boosted_once;
    int timer_boost_enabled;
    int boost_enable_steps;
    int boost_disable_steps;
    int iterator;
} obstacle0_state;

extern obstacle0_state obstacle0_status;
extern obstData obst_data;
extern uint8_t player[32][2]; // Player pixel coordinates is globally is accesible to all c files
extern uint8_t collision_sensors[9][2];
extern uint8_t frame[316][2];
extern uint8_t intro[165][2];
extern uint8_t (*live_obstacles_pointer)[MAX_LIVE_OBST][LIVE_SIZE][2]; // live object array pointer is accesible to all c files

/**
 * @brief Initializes the live object array
 * every index is set to ENDOF
 * ENDOF signifies end of array, so that array is not read past ENDOF
 * 
 */
void init_live ();

/**
 * @brief Randomly picks an obstacle type to go live
 * If there is no free spot on the live obstacles array no obstacle
 * is generated
 * 
 * if there is already an obstacles of type 0, no new 
 * obstacle of that type is to be generated
 */
void generate_obstacle();

/**
 * @brief checks wheter there is an obstacles of a certain type
 * on the array of live obstacles
 * 
 * @param obstnr either 0, 1, or 2 for obst0, obst1, obst2
 * @return int 1 if there is an obstacle of that type, else 0
 */
int is_there_obstX_live(int obstnr);

/**
 * @brief This function move obstacle types 0 and 2 up or down
 * 
 * Should only be used for obstacle types 0 and 2
 * 
 * @param obstnr obst type to be moved
 */
void move_up_down_obstX (int obstnr);

/**
 * @brief updates the limit of up-down movement of obstacle types 0 and 2
 * if the obstacle has reach top of OLED, limit is updated to 30
 * indicating that it has reached the top and obstacle should not be moved up anymore
 * 
 * if it has reach bottom of oled, limit is update to 1
 * indicating that it has reached the bottom and obstacle should not be moved down anymore
 * 
 * this function is used to make sure we do not lets obstacle coordinates get outside
 * of the OLED
 * 
 * @param obstnr obst type to update limit of
 * @param index the index at which obstacle lies in the live obstacles array
 * @param limit the limit to set to, either 1 or 30
 */
void update_limit_obstX (int obstnr, int index, int limit);

/**
 * @brief Get the limit of obstX
 * should only be used for obst types 0 and 2
 * 
 * @param obstnr obst type
 * @param index the index at which obstacle lies in the live obstacles array
 * @return int the value of the limit
 */
int get_limit_of_obstX (int obstnr, int index);

/**
 * @brief returns the index of obst0 in the live obstacles array
 * 
 * @return int index in the array, if there is no obst0 in the array return -1
 */
int index_of_obst0 ();

/**
 * @brief collision check between obstacles and collision sensor
 * 
 * @return int returns 1 if collision detected, else 0
 */
int collision_check ();

/**
 * @brief resets player pixel coordinates and collision coordinates to initial state
 * this function is used when the player want to restart after death
 * 
 */
void reset_player ();

/**
 * @brief removes an obstacle from the live objects array
 * 
 * @param index index at which the obstacle is in
 */
void disassemble_obstacle (int index);

/**
 * @brief initializes obstData struct
 * 
 */
void init_obstacle_Data ();
