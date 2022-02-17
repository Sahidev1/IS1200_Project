#include <pic32mx.h>
#include <stdint.h>
#include "game_header.h"

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

#define COLUMNS 128
#define ROWS 32
#define PAGE_COUNT 4

void quicksleep (int cycles){
    while (cycles-- > 0);
}

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

void display_init(void) {
    DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}

void render (){
    int buffer_index = 0;
    int i, j;
    for (i = 0; i < PAGE_COUNT; i++){
        DISPLAY_CHANGE_TO_COMMAND_MODE;
        spi_send_recv(0x22);
        spi_send_recv(i);
        
        spi_send_recv(0x00);
        spi_send_recv(0x10);
        
        DISPLAY_CHANGE_TO_DATA_MODE;

        for (j = 0; j < BUFFER_SIZE/PAGE_COUNT; j++){
            spi_send_recv(display_buffer[buffer_index++]);
        }
    }
}

void movePixels (int steps, int array_rows, int array_columns, char direction, uint8_t* arr){
    int i;
    switch (direction)
    {
    case 'r':
        for (i = 0; i < array_rows; i++){
            *(arr + i*array_columns + 1) += steps;
        }
        break;
    case 'l':
        for (i = 0; i < array_rows; i++){
            *(arr + i*array_columns + 1) -= steps;
        }
        break;
    case 'u':
        for (i = 0; i < array_rows; i++){
            *(arr + i*array_columns) += steps;
        }
        break;
    case 'd':
        for (i = 0; i < array_rows; i++){
            *(arr + i*array_columns) -= steps;
        }
        break;
    default:
        break;
    }
}

void setPixel (int row, int column){
    int page = row / 8;
    uint8_t row_byte = ((uint8_t)row) % 8;
    int array_pos = page*128 + column;

    display_buffer[array_pos] = display_buffer[array_pos] | pow2(row_byte);
}

void setPixels (int array_rows, int array_columns, uint8_t* pixelArray){
    int i, j;
    for (i = 0; i < array_rows; i++){
        setPixel(*(pixelArray + i*array_columns),*(pixelArray + i*array_columns + 1));
    }
}

void clearPixel (int row, int column){
    int page = row / 8;
    uint8_t row_byte = ((uint8_t)row) % 8;
    int array_pos = page*128 + column;

    display_buffer[array_pos] = display_buffer[array_pos] & (~pow2(row_byte));
}

void clearPixels (int array_rows, int array_columns, uint8_t* pixelArray){
    int i, j;
    for (i = 0; i < array_rows; i++){
        clearPixel(*(pixelArray + i*array_columns),*(pixelArray + i*array_columns + 1));
    }
}

void clearDisplay (){
    int i, j;
    for (i = 0; i < ROWS; i++){
        for (j = 0; j < COLUMNS; j++){
            clearPixel(i, j);
        }
    }
    render();
}

