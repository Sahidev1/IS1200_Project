#include <pic32mx.h>
#include "game_header.h"
#include "graphical_objects.h"

char textbuffer[4][16];
uint8_t display_buffer[BUFFER_SIZE];
int btn_stat = 0;

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

    game_state_.current_score = 0;
    

    int flag = 0;
    init_live();
    init_delays();
    init_game_state();
    set_frame_pixels(ON);

    while(true){
        set_intro_pixels(ON);
        render ();
        accurate_delay (5000);
        set_intro_pixels(OFF);
        render ();
        while (game_state_.player){
            btn_stat = getbtns();
            direction = read_direction(btn_stat);
            if (check_generator_delay(game_state_.gen_delay)){
                generate_obstacle();
            }
            LED_debugger (game_state_.current_score);
            
            setPlayerPixels(ON, 32,player[0]);
            setLiveObstaclePixels(ON);
        
            render();

            setPlayerPixels(OFF, 32, player[0]);
            setLiveObstaclePixels(OFF);
        
            
            if (check_obst2_delay(game_state_.obst2_up_down_delay)){
                if (is_there_obstX_live(2)){
                    move_up_down_obstX(2);
                }
            }

            if (check_obst0_delay(game_state_.obst2_up_down_delay)){
                if (is_there_obstX_live(0) && !obstacle0_status.boost_enabled){
                    move_up_down_obstX(0);
                }
            }
            
            int obst_delay = check_obstacle_delay(game_state_.live_obstacle_delay);
            if (obst_delay){
                moveLiveObjPixels(1, LEFT);
                if (is_there_obstX_live(0) && !obstacle0_status.boost_enabled){
                    obstacle0_status.iterator++;
                }
            }

            if (is_there_obstX_live(0) && obst_delay){
                if (!obstacle0_status.boost_enabled && !obstacle0_status.boosted_once){
                    if (obstacle0_status.iterator >= obstacle0_status.boost_disable_steps){
                        obstacle0_status.boost_enabled = true;
                        obstacle0_status.iterator = 0;
                        set_obst0_boost_delay(obstacle0_status.timer_boost_enabled);
                    }
                }
                else {
                    if (obstacle0_status.iterator >= obstacle0_status.boost_enable_steps){
                        obstacle0_status.boost_enabled = false;
                        obstacle0_status.boosted_once = true;
                        obstacle0_status.iterator = 0;
                    }
                }
            }
            boolean part1 = is_there_obstX_live(0) && !obstacle0_status.boosted_once;
            boolean part2 = obstacle0_status.boost_enabled && check_obst0_boost_delay();
            if (part1 && part2){
                int index = index_of_obst0();
                moveObjectPixels (index,1, LEFT);
                obstacle0_status.iterator++;
            }
            
            if (btn_stat && check_player_delay(20)){
                movePlayerPixels (steps, 32, direction, player[0]);
                movePlayerPixels (steps, 9, direction, collision_sensors[0]);
            }
            if (collision_check()) game_state_.player = DEAD;
        }
    }
    
    while(1);
	return 0;
}
