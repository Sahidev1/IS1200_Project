#include <pic32mx.h>

#define ENDOF 255 // Used for signifying the end of valid values to read in live objects array
#define PIXEL_REACHED_END 254 // Signifies that an obstacles pixel coordinate has reached end of OLED
#define ROW_COORD_OUT_OF_BOUNDS 253 // signifies that pixel coordinate is out of bound ROW range [0,31]
#define LIVE_SIZE 145 // size of live object array
#define MAX_LIVE_OBST 3 // max live obstacles

#define FILLED 1
#define EMPTY 0

typedef enum {false, true} boolean;

typedef struct Obstacle_Data {
    int filled_array_indexes[3];
    int obstacle_type_at_array_indexes[3];
    int obst2_limit_value[3];
    int obst0_limit_value[3];
} obstData;

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
extern uint8_t (*live_obstacles_pointer)[MAX_LIVE_OBST][LIVE_SIZE][2]; // live object array pointer is accesible to all c files

void init_live ();

void generate_obstacle();

int is_there_obstX_live(int obstnr);

void move_up_down_obstX (int obstnr);

void update_limit_obstX (int obstnr, int index, int limit);

int get_limit_of_obstX (int obstnr, int index);

int index_of_obst0 ();

int collision_check ();

void init_gfo ();

void disassemble_obstacle (int index);

