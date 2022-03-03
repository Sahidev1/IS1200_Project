#include <pic32mx.h>
#include <stdint.h>

#define BUFFER_SIZE 512 // Size of display buffer
#define COLUMNS 128 // columns of pixels on OLED
#define ROWS 32 // rows of pixels on OLED
#define PAGE_COUNT 4 // number of 8 pixel high rows

// direction definitions
#define UP 'u'
#define DOWN 'd'
#define RIGHT 'r'
#define LEFT 'l'

// ON OFF definitions
#define OFF 0
#define ON 1

typedef enum{DEAD, ALIVE} Player;

typedef struct Game_state {
    int current_score;
    int gen_delay;
    int obst2_up_down_delay;
    int obst0_up_down_delay;
    int live_obstacle_delay;
    Player player;
}game_state;

extern game_state game_state_;

/* Display related */
extern char textbuffer[4][16];

extern uint8_t display_buffer[BUFFER_SIZE]; // display buffer that is accessible by any c file in the program

extern int obstacle_move_delay;
extern int player_move_delay;

uint8_t spi_send_recv(uint8_t data);

void display_init(void);

void render ();

void movePlayerPixels (int steps, int array_rows, char direction, uint8_t* arr);

void moveObjectPixels (int arr_index, int steps, char direction);

void moveLiveObjPixels (int steps, char direction);

void setPixel (int on_off,int row, int column);

void setObjectPixels (int ON_OFF,int live_index);

void setLiveObstaclePixels (int ON_OFF);

void setPlayerPixels (int ON_OFF,int array_rows, uint8_t* pixelArray);

void set_frame_pixels (int ON_OFF);

void set_intro_pixels (int ON_OFF);

void clearDisplay ();

void quicksleep();



/* IO/Interrupt related */
extern int btn_stat;

void Initialize_IO( void );

void user_isr(void);

int getbtns (void);

void accurate_delay (int ms);

void init_delays ();

int check_obstacle_delay (int ms);

int check_player_delay (int ms);

int check_generator_delay (int ms);

int check_obst2_delay (int ms);

void set_obst0_boost_delay (int ms);

int check_obst0_boost_delay ();

int check_obst0_delay (int ms);

char read_direction (int btn_stat);

/* game state */
void init_game_state ();
void increase_score();


/* utility/helper functions */
void LED_debugger (int val);

int random_number (int range);

int obstacle_gen_rand (int range);

int random_number_between (int lower, int upper);

uint8_t pow2 (uint8_t exponent);

