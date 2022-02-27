#include <pic32mx.h>
#include <stdint.h>
#include "game_header.h"
int delay_counter = 0;

/**
 * @brief Interuptions Service Routine that handles interrupts in
 * the program
 * 
 */
void user_isr(void){
    IFSCLR(0) = 0x100;
    if (delay_counter == INT32_MAX){
        delay_counter == 0;
    }
    delay_counter++;
}

/**
 * @brief creats a millisecond accuracy delay
 * 
 * @param ms milliseconds delay
 */
void accurate_delay (int ms){
    delay_counter = 0;
    while (delay_counter < ms);
}

/** 
    reads switch 1,2,3,4 status
    returns a value with ON/OFF status of switches at
    4 least significant bits
    code taken from LAB 3
*/
int getsw (void){
    return (PORTD & (0xf << 8)) >> 8;
}

/**
    reads BTN 1,2,3,4 status
    returns a value with ON/OFF status of buttons at
    4 least significant bits
    code taken from LAB 3
*/
int getbtns (void) {
    return ((PORTD & (0b111 << 5)) >> 4) | ((PORTF & 0x2) >> 1);
}

/**
    translates direction from button pushed
*/
char read_direction (int btn_stat){
    switch (btn_stat)
    {
    case 1:
        return DOWN;
    case 2: 
        return RIGHT;
    case 4:
        return UP;
    case 8:
        return LEFT;
    default:
        break;
    }
    return 0;
}

/**
    This function initializes the LEDs, Button, switches and timer 2
    Code is taken from LAB 3
*/
void Initialize_IO( void )
{
    volatile unsigned* port_E_IO = (volatile unsigned*) 0xBF886100;
    *port_E_IO = *port_E_IO & (~0xff);

    volatile unsigned* port_E = (volatile unsigned*) 0xBF886110;
    *port_E = 0x0;

    TRISD = TRISD | (0b1111111 << 5);
    TRISFSET = 0x2;


    /* Setting up timer 2 */

    // disabling timer 2
    T2CONCLR = 0x8000;

    // Initialize timer value to 0
    TMR2 = 0; 

    // setting TCPKS, prescaling at 1:256
    T2CON = T2CON & 0xffffff8f;
    T2CON = T2CON | 0x70;

    // setting TCS, setting to peripheral clock
    T2CON = T2CON & (~0x2);

    // setting T32 to 16 bit mode.
    T2CON = T2CON & (~0x8);

    // setting period register bits
    // one period is 31250 prescaled cycle periods. 
    PR2 = 31250 / 100;

    // setting interupt flag for timer 2
    IECSET(0) = 0x100;

    // Setting interrupt priority and subpriority to max 
    IPC(2) = 0x1f;

    // clearing interrupt flag bit
    IFSCLR(0) = 0x100;

    enable_interrupt(); 

    // starting timer 2
    T2CONSET = 0x8000;   

    return;
}

void LED_debugger (int val){
    PORTE = val;
}

/**
    Helper function that calculates powers of 2
    argument N will output 2^N
*/
uint8_t pow2 (uint8_t exponent){
    if (exponent == 0) return 1;
    return (uint8_t) 2 << (exponent - 1);
}
