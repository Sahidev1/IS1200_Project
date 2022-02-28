#include <pic32mx.h>
#include "game_header.h"
#include <stdlib.h>
#include "graphical_objects.h"

char textbuffer[4][16];
uint8_t display_buffer[BUFFER_SIZE];
int btn_stat = 0;


typedef struct Gfo_state
{
    uint8_t *gfo_pointers[10];
}gfo_state;

void gen_obstacle (int obst_nr){

}

int main() {
    /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */

    /* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

    /* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
        SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

    display_init();
    quicksleep(100000);
    clearDisplay();
    quicksleep(1000);
    Initialize_IO();
    
    int direction;
    int steps = 1;
    int btn_stat;
    
    int delay;

    int flag = 0;
    init_live();
    init_delays();
    while (1){
        btn_stat = getbtns();
        direction = read_direction(btn_stat);
        if (check_generator_delay(2500)){
            generate_obstacle();
        }
        
        setPlayerPixels(ON, 32,player[0]);
        setLiveObstaclePixels(ON);
        
        render();

        setPlayerPixels(OFF, 32, player[0]);
        setLiveObstaclePixels(OFF);
        LED_debugger(*(live_obstacles_pointer[0][0][0]));
        

        delay = check_obstacle_delay(50);
        if (delay) moveLiveObjPixels(1, LEFT);
        
        if (btn_stat && check_player_delay(20)){
            movePlayerPixels (steps, 32, direction, player[0]);
            movePlayerPixels (steps, 9, direction, collision_sensors[0]);
        }
        if (collision_check()) break;
    }
    
    while(1);
	return 0;
}
