#include <pic32mx.h>

#define ENDOF 255
#define PIXEL_REACHED_END 254
#define LIVE_SIZE 100

extern uint8_t player[32][2];
uint8_t collision_sensors[9][2];

extern uint8_t (*live_objects_pointer)[3][100][2];

extern  uint8_t obst1_live[51][2];

extern uint8_t live_obj0[100][2];

void reset_obst ();

void init_live ();

void generate_obstacle();

int collision_check ();

void init_gfo ();

void disassemble_obstacle (int index);

