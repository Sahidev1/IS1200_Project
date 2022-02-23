#include <pic32mx.h>
#include <stdint.h>

#define BUFFER_SIZE 512

#define UP 'u'
#define DOWN 'd'
#define RIGHT 'r'
#define LEFT 'l'


/* Display related */
extern char textbuffer[4][16];
extern uint8_t display_buffer[BUFFER_SIZE];

uint8_t spi_send_recv(uint8_t data);

void display_init(void);

void render ();

void movePixels (int steps, int array_rows, char direction, uint8_t* arr);

void moveObjectPixels (int steps, int array_rows, char direction, uint8_t* arr);

void setPixel (int row, int column);

void setPixels (int array_rows, uint8_t* pixelArray);

void clearPixel (int row, int column);

void clearPixels (int array_rows, uint8_t* pixelArray);

void clearDisplay ();

void quicksleep();



/* IO/Interrupt related */
extern int btn_stat;

void Initialize_IO( void );

void user_isr(void);

int getbtns (void);

void buffer_update ();

void accurate_delay (int ms);

char read_direction (int btn_stat);




void game ();


void user_isr(void);

uint8_t pow2 (uint8_t exponent);

