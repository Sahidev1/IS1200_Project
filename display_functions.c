#include <pic32mx.h>
#include <stdint.h>
#include "game_header.h"
#include "graphical_objects.h"

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)



/**
 * @brief useful delay tool that's not dependent on timers
 * Inspired by Fredrik Lundevalls quicksleep implementation
 * 
 * @param cycles 
 */
void quicksleep (int cycles){
    while (cycles-- > 0);
}

/**
 * @brief sends data and receives data from SPI
 * 
 * @param data byte to send
 * @return uint8_t byte received
 */
uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

/**
 * @brief Initializes the OLED On the chipkit
 * Code is taken from LAB3
 */
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

/**
 * @brief Renders the data in display_buffer to OLED
 * Each byte represents an 8 pixel column on a page
 * 
 */
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

/**
 * @brief Moves the players pixel coordinates up, down, left or right
 * 
 * @param steps number of pixels to move across at certains direction
 * @param array_rows number of (x,y) pixel coordinates in 2d array
 * @param direction direction to move pixel coordinates
 * @param arr array that contains pixel coordinates
 */
void movePlayerPixels (int steps, int array_rows, char direction, uint8_t* arr){
    int array_columns = 2;
    int i;
    int flag = 1;
    int offset;
    int limit;

    switch (direction)
    {
    case RIGHT:
            offset = 1;
            limit = COLUMNS - 1;
        break;
    case LEFT: 
            offset = 1;
            steps = -1 * steps;
            limit = 0;
        break;
    case UP:
            offset = 0;
            steps = -1 * steps;  
            limit = 0;
        break;
    case DOWN:
            offset = 0;
            limit = ROWS - 1;
        break;
    default:
        break;
    }

    for (i = 0; i < array_rows; i++){
        if (*(arr + i*array_columns + offset) == limit){
            return;
        }
    }
    for (i = 0; i < array_rows; i++){
        *(arr + i*array_columns + offset) += steps;
    }
}



/**
 * @brief Moves non-player object pixel coordinates, such as obstacles
 * 
 * @param arr_index which obstacle on array of live obstacles to move
 * @param steps pixels to move across in a certain direction
 * @param direction direction up,down,left or right
 */
void moveObjectPixels (int arr_index, int steps, char direction){
    int array_columns = 2;
    int i, k;
    int limit;
    k = arr_index;
    int out_of_display_flag = 1;
    switch (direction)
    {
    case RIGHT:
        break;
    case LEFT:
        for (i = 0; i < LIVE_SIZE; i++){
            if ((*live_obstacles_pointer)[k][i][0] == ENDOF) break;
            if ((*live_obstacles_pointer)[k][i][1] < PIXEL_REACHED_END){
                out_of_display_flag = 0;
            }
            if ((*live_obstacles_pointer)[k][i][1] == 0){
                (*live_obstacles_pointer)[k][i][1] = PIXEL_REACHED_END;
            }
            if ((*live_obstacles_pointer)[k][i][1] != PIXEL_REACHED_END) {
                (*live_obstacles_pointer)[k][i][1] -=steps;
            }
        }
        break;
    case DOWN:
        limit = ROWS - 2;
        for (i = 0; i < LIVE_SIZE; i++){
            if ((*live_obstacles_pointer)[k][i][0] == ENDOF) break;
            if ((*live_obstacles_pointer)[k][i][0] == limit){
                if (obst_data.obstacle_type_at_array_indexes[k] == 2){
                    update_limit_obstX (2, k, limit);
                }
                if (obst_data.obstacle_type_at_array_indexes[k] == 0){
                    update_limit_obstX (0, k, limit);
                }
                return;
            }
        }
        for (i = 0; i < LIVE_SIZE; i++){
            if ((*live_obstacles_pointer)[k][i][0] == ENDOF) break;
            (*live_obstacles_pointer)[k][i][0] += steps;
        }
        break;
    case UP:
        limit = 1;
        for (i = 0; i < LIVE_SIZE; i++){
            if ((*live_obstacles_pointer)[k][i][0] == ENDOF) break;
            if ((*live_obstacles_pointer)[k][i][0] == limit){
                if (obst_data.obstacle_type_at_array_indexes[k] == 2){
                    update_limit_obstX (2, k, limit);
                }
                if (obst_data.obstacle_type_at_array_indexes[k] == 0){
                    update_limit_obstX (0, k, limit);
                }
                return;
            }
        }
        for (i = 0; i < LIVE_SIZE; i++){
            if ((*live_obstacles_pointer)[k][i][0] == ENDOF) break;
            (*live_obstacles_pointer)[k][i][0] -= steps;
        }
        break;
    default:
        break;
    }
    if (direction == LEFT && out_of_display_flag){
        disassemble_obstacle(k);
    }   
}

void moveLiveObjPixels (int steps, char direction){
    int * arr_p = obst_data.filled_array_indexes;
    int i;
    for (i = 0; i < MAX_LIVE_OBST; i++){
        if (*(arr_p + i) == FILLED){
            moveObjectPixels(i,steps,direction);
        }
    }
}

/**
 * @brief This function sets the status of 1 pixel in the display buffer
 * 
 * @param on_off set pixel to on or off, 0 or 1
 * @param row the row of the pixel on the oled
 * @param column the column of the pixel on the oled
 */
void setPixel (int on_off,int row, int column){
    if (row >= 32 || column >= 128) return;
    int page = row / 8;
    uint8_t row_byte = ((uint8_t)row) % 8;
    int array_pos = page*128 + column;

    if (on_off == ON){
        display_buffer[array_pos] = display_buffer[array_pos] | pow2(row_byte);
    }
    else {
        display_buffer[array_pos] = display_buffer[array_pos] & (~pow2(row_byte));
    }
}

void set_frame_pixels (int ON_OFF){
    int i;
    for (i = 0; i < 316; i++){
        setPixel (ON_OFF, frame[i][0], frame[i][1]);
    }
}

/**
 * @brief Puts an objects pixel coordinates on the display buffer
 * 
 * @param ON_OFF whether to turn off the objects pixels, or turn on
 * @param live_index which obstacle in array of obstacles
 */
void setObjectPixels (int ON_OFF,int live_index){
    int array_columns = 2;
    int i, k;
    k = live_index;
    for (i = 0; i < LIVE_SIZE && (*live_obstacles_pointer)[k][i][0] != ENDOF; i++){
        setPixel(ON_OFF,(*live_obstacles_pointer)[k][i][0],(*live_obstacles_pointer)[k][i][1]);
    }
}

void setLiveObstaclePixels (int ON_OFF){
    int * arr_p = obst_data.filled_array_indexes;
    int i;
    for (i = 0; i < MAX_LIVE_OBST; i++){
        if (*(arr_p + i) == FILLED){
            setObjectPixels(ON_OFF, i);
        }
    }
}

/**
 * @brief Returns pixel value of an OLED coordinate from display buffer
 * 
 * @param row pixel row on OLED
 * @param column pixel column on OLED
 * @return int 
 */
int getPixel (int row, int column){
    int page = row / 8;
    uint8_t row_byte = ((uint8_t)row) % 8;
    int array_pos = page*128 + column;

    return (display_buffer[array_pos] & (pow2(row_byte))) >> row_byte;
}

/**
 * @brief Put the players pixel coordinates into the display buffer
 * 
 * @param ON_OFF set the players pixels to on or off, on the display buffer
 * @param array_rows number of (x,y) coordinates in 2d pixel coordinate array
 * @param pixelArray array of pixel coordinates
 */
void setPlayerPixels (int ON_OFF,int array_rows, uint8_t* pixelArray){
    int array_columns = 2;
    int i, j;
    for (i = 0; i < array_rows && *(pixelArray + i*array_columns) != ENDOF; i++){
        setPixel(ON_OFF,*(pixelArray + i*array_columns),*(pixelArray + i*array_columns + 1));
    }
}

/**
 * @brief Clears the entire display buffer
 * 
 */
void clearDisplay (){
    int i, j;
    for (i = 0; i < ROWS; i++){
        for (j = 0; j < COLUMNS; j++){
            setPixel(OFF, i, j);
        }
    }
    render();
}


