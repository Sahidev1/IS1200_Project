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
    
    int flag = 0;
    reset_live();
    reset_obst();
    while (1){
        btn_stat = getbtns();
        direction = read_direction(btn_stat);
        
        setPixels(32,player[0]);
        //setPixels(30, 2,obst0[0]);
        setPixels(100,live_obj0[0]);

        render();
        //quicksleep();
        clearPixels(32, player[0]);
        //clearPixels(30, 2, obst0[0]);
        clearPixels(100, live_obj0[0]);

        accurate_delay (30);
        //movePixels (1, 30, 2, 'l', obst0[0]);
        moveObjectPixels(1,100,LEFT,live_obj0[0]);
        if (btn_stat){
            movePixels (steps, 32, direction, player[0]);
            movePixels (steps, 9, direction, collision_sensors[0]);
        }
        flag = collision_check();
        if (flag == 1) break;
    }

    while(1);
	return 0;
}
