#include <pic32mx.h>
#include <stdint.h>
#include "game_header.h"
int delay_counter = 0;

void user_isr(void){
    IFSCLR(0) = 0x100;
    if (delay_counter == INT32_MAX){
        delay_counter == 0;
    }
    delay_counter++;
}

void accurate_delay (int ms){
    delay_counter = 0;
    while (delay_counter < ms);
}

// reads GPIO pin 8 to 11 status
int getsw (void){
    return (PORTD & (0xf << 8)) >> 8;
}

// reads GPIO pin 5 to 7 status
int getbtns (void) {
    return ((PORTD & (0b111 << 5)) >> 4) | ((PORTF & 0x2) >> 1);
}

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

void Initialize_IO( void )
{
    volatile unsigned* port_E_IO = (volatile unsigned*) 0xBF886100;
    *port_E_IO = *port_E_IO & (~0xff);

    volatile unsigned* port_E = (volatile unsigned*) 0xBF886110;
    *port_E = 0x0;

    //TRISD: 0xBF8860C0
    //PORTD: 0xBF8860D0

    TRISD = TRISD | (0b1111111 << 5);
    TRISFSET = 0x2;

    // Setting up timer 2

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

    //IFSSET(0) = 0x100;
    
    enable_interrupt(); 

    // starting timer 2
    T2CONSET = 0x8000;   

    return;
}

uint8_t pow2 (uint8_t exponent){
    if (exponent == 0) return 1;
    return (uint8_t) 2 << (exponent - 1);
}
