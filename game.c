#include <pic32mx.h>
#include "game_header.h"
#include <stdint.h>

uint8_t pixmap[70][2] = {{14,5},{14,6},{14,7},{26,7},{13,8},
{24,8},{25,8},{4,9},{5,9},{6,9},
{7,9},{13,9},{23,9},{3,10},{8,10},
{13,10},{21,10},{22,10},{3,11},{8,11},
{13,11},{20,11},{2,12},{9,12},{12,12},
{18,12},{19,12},{2,13},{9,13},{10,13},
{11,13},{12,13},{13,13},{14,13},{15,13},
{16,13},{17,13},{18,13},{2,14},{9,14},
{12,14},{19,14},{20,14},{2,15},{8,15},
{12,15},{21,15},{3,16},{8,16},{11,16},
{22,16},{23,16},{4,17},{5,17},{6,17},
{7,17},{11,17},{24,17},{11,18},{25,18},
{26,18},{11,19},{27,19},{10,20},{10,21},
{10,22},{10,23},{9,24},{9,25},{9,26}
};


void game (){
    
    int btn_stat = getbtns();
    char direction; 

    switch (btn_stat)
    {
    case 1:
        direction = 'd';
        break;
    case 2: 
        direction = 'r';
        break;
    case 4:
        direction = 'u';
        break;
    case 8:
        direction = 'l';
        break;
    default:
        break;
    }

    int steps = 1;
    
    setPixels(70,2,pixmap[0]);
    render();
    //quicksleep();
    clearPixels(70,2,pixmap[0]);

    if (btn_stat){
        accurate_delay (25);
        movePixels (steps, 70, 2, direction, pixmap[0]);
    }
    
}
