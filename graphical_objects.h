#include <pic32mx.h>

extern uint8_t player[32][2];
uint8_t collision_sensors[9][2];
extern  uint8_t obst1_live[51][2];

void reset_obst ();

int collision_check ();

void init_gfo ();

