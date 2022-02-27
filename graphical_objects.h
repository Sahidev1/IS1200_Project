#include <pic32mx.h>

#define ENDOF 255 // Used for signifying the end of valid values to read in live objects array
#define PIXEL_REACHED_END 254 // Signifies that an obstacles pixel coordinate has reached end of OLED
#define ROW_COORD_OUT_OF_BOUNDS 253 // signifies that pixel coordinate is out of bound ROW range [0,31]
#define LIVE_SIZE 145 // size of live object array
#define MAX_LIVE_OBST 3 // max live obstacles

extern uint8_t player[32][2]; // Player pixel coordinates is globally is accesible to all c files
extern uint8_t collision_sensors[9][2];

extern uint8_t (*live_obstacles_pointer)[MAX_LIVE_OBST][LIVE_SIZE][2]; // live object array pointer is accesible to all c files

void reset_obst ();

void init_live ();

void generate_obstacle();

int collision_check ();

void init_gfo ();

void disassemble_obstacle (int index);

