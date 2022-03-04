#include <pic32mx.h>
#include "game_header.h"
#include "graphical_objects.h"

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
    Initialize_IO();
    
    int direction;
    int steps = 1;
    int btn_stat;
    int switch_stat = 0;
    int delay;
    
    boolean first_run = true;
    boolean restart = false;

    init_live(); // initialize live obstacles array
    init_delays(); // initlize delay variables
    init_game_state(); // initialize game_State struct
    init_obstacle_Data(); // initialize obstacle_data struct
    set_frame_pixels(ON); // turn on frame pixels

    while(true){
        //if first run show intro image
        if (first_run){
            set_intro_pixels(ON);
            render ();
            accurate_delay (5000);
            set_intro_pixels(OFF);
            render (); 
            first_run = false; 
        }

        // if restart, reinitialize
        if (restart){
            init_live();
            init_delays();
            init_game_state();
            init_obstacle_Data();
            set_frame_pixels(ON);
        }

        // while player is alive
        while (game_state_.player_status){
            btn_stat = getbtns();
            direction = read_direction(btn_stat);
            if (check_generator_delay(game_state_.gen_delay)){
                generate_obstacle();
            }
            
            // set player and obstacles in the displaybuffer
            setPlayerPixels(ON, 32,player[0]);
            setLiveObstaclePixels(ON);

            // render display buffer
            render();

            // remove player and obstacles from the displaybuffer
            setPlayerPixels(OFF, 32, player[0]);
            setLiveObstaclePixels(OFF);
        
            // should obstacle of type 2 be moved up/down 
            if (check_obst2_delay(game_state_.obst2_up_down_delay)){
                if (is_there_obstX_live(2)){
                    move_up_down_obstX(2);
                }
            }

            // should obstacle of type 0 be moved up/down 
            if (check_obst0_delay(game_state_.obst2_up_down_delay)){
                if (is_there_obstX_live(0) && !obstacle0_status.boost_enabled){
                    move_up_down_obstX(0);
                }
            }
            
            int obst_delay = check_obstacle_delay(game_state_.live_obstacle_delay);

            // increment obst0 boost-disabled step counter
            if (obst_delay){
                // move all obstacles a step to the left
                moveLiveObjPixels(1, LEFT);

                if (is_there_obstX_live(0) && !obstacle0_status.boost_enabled){
                    obstacle0_status.iterator++;
                }
            }

            // update obst0 status
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

            // if boost is enabled, boosts obst0
            if (part1 && part2){
                int index = index_of_obst0();
                moveObjectPixels (index,1, LEFT);
                obstacle0_status.iterator++;
            }
            
            // update player pixel position depending on button inputs
            if (btn_stat && check_player_delay(20)){
                movePlayerPixels (steps, 32, direction, player[0]);
                movePlayerPixels (steps, 9, direction, collision_sensors[0]);
            }
            
            // check for colision between play and obstacle
            if (collision_check()){ 
                game_state_.player_status = DEAD;
                break;
            }
            
            // Used here to display score on LEDS
            LED_debugger(game_state_.current_score);
        }

        // if player dead display score until player flips a switch
        if (!game_state_.player_status){
            accurate_delay (500);
            clearDisplay();
            char * score_str = score_string_gen(game_state_.current_score);
            display_string (0, score_str);
            display_string (2,"Flip a switch");
            display_string (3, "to restart");
            display_update(); 

            while (!switch_stat){
                switch_stat = getsw(); 
            }
            switch_stat = 0;
            restart = true;
            reset_player();
            clearDisplay();
        }
    }
	return 0;
}
