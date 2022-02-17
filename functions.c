#include <pic32mx.h>
#include <stdint.h>

void user_isr(void){
    return;
}

uint8_t pow2 (uint8_t exponent){
    if (exponent == 0) return 1;
    return (uint8_t) 2 << (exponent - 1);
}