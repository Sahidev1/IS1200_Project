#include <pic32mx.h>

#define ENDOF 255
#define PIXEL_REACHED_END 254

extern uint8_t player[32][2];
uint8_t collision_sensors[9][2];
extern  uint8_t obst1_live[51][2];

extern uint8_t live_obj0[100][2];

void reset_obst ();

void reset_live();

int collision_check ();

void init_gfo ();

