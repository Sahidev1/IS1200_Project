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

/**
 * @brief A struct the keeps track of the game state
 * 
 */
typedef struct Game_state {
    int current_score;
    int gen_delay;
    int obst2_up_down_delay;
    int obst0_up_down_delay;
    int live_obstacle_delay;
    Player player_status;
}game_state;

extern game_state game_state_;

/* Display related */

extern char textbuffer[4][16];
extern const uint8_t const font[128*8];

extern uint8_t display_buffer[BUFFER_SIZE]; // display buffer that is accessible by any c file in the program

/**
 * @brief sends data and receives data from SPI
 * 
 * @param data byte to send
 * @return uint8_t byte received
 */
uint8_t spi_send_recv(uint8_t data);

/**
 * @brief Initializes the OLED On the chipkit
 * Code is taken from LAB3
 */
void display_init(void);

/**
 * @brief Renders the data in display_buffer on the OLED
 * Each byte represents an 8 pixel column on a page
 * 
 */
void render ();

/**
 * @brief Moves the players pixel coordinates up, down, left or right
 * 
 * @param steps number of pixels to move across at certains direction
 * @param array_rows number of (x,y) pixel coordinates in 2d array
 * @param direction direction to move pixel coordinates
 * @param arr array that contains pixel coordinates
 */
void movePlayerPixels (int steps, int array_rows, char direction, uint8_t* arr);

/**
 * @brief Moves non-player object pixel coordinates, such as obstacles
 * 
 * @param arr_index which obstacle on array of live obstacles to move
 * @param steps pixels to move across in a certain direction
 * @param direction direction up,down,left or right
 */
void moveObjectPixels (int arr_index, int steps, char direction);

/**
 * @brief moves all live obstacles in the live obstacles array
 * 
 * @param steps steps to move each obstacle
 * @param direction direction to move each obstacle
 */
void moveLiveObjPixels (int steps, char direction);

/**
 * @brief This function sets the status of 1 pixel in the display buffer 
 * function is limited to row coordinates [1, 30] and column coordinates
 * [1,126] on the OLED
 * 
 * @param on_off set pixel to on or off, 0 or 1
 * @param row the row of the pixel on the oled
 * @param column the column of the pixel on the oled
 */
void setPixel (int on_off,int row, int column);

/**
 * @brief Puts an objects pixel coordinates on the display buffer
 * 
 * @param ON_OFF whether to turn off the objects pixels, or turn on
 * @param live_index which obstacle in array of obstacles
 */
void setObjectPixels (int ON_OFF,int live_index);

/**
 * @brief Sets all live obstacles pixel coordinates on the display buffer
 * 
 * @param ON_OFF turn the pixels on or off
 */
void setLiveObstaclePixels (int ON_OFF);

/**
 * @brief Put the players pixel coordinates into the display buffer
 * 
 * @param ON_OFF set the players pixels to on or off, on the display buffer
 * @param array_rows number of (x,y) coordinates in 2d pixel coordinate array
 * @param pixelArray array of pixel coordinates
 */
void setPlayerPixels (int ON_OFF,int array_rows, uint8_t* pixelArray);

/**
 * @brief Sets the graphical frames pixels
 * 
 * @param ON_OFF on or off
 */
void set_frame_pixels (int ON_OFF);

/**
 * @brief Sets the pixels of the game introduction image
 * 
 * @param ON_OFF on or off
 */
void set_intro_pixels (int ON_OFF);

/**
 * @brief Clears the entire display buffer
 * 
 */
void clearDisplay ();

/**
 * @brief useful delay tool that's not dependent on timers
 * Inspired by Fredrik Lundevalls quicksleep implementation
 * 
 * @param cycles 
 */
void quicksleep();

/**
 * @brief puts a string on the textbuffer
 * 
 * @param line which page on OLED
 * @param s string to write
 * 
 * Code is taken from LAB3 files
 */
void display_string(int line, char *s);

/**
 * @brief the textbuffer is rendered on the OLED
 * 
 * Code is taken from LAB3 files
 */
void display_update(void);



/* IO/Interrupt related */

extern int btn_stat;

/**
    This function initializes the LEDs, Button, switches and timer 2
    Code is taken from LAB 3
*/
void Initialize_IO( void );

/**
 * @brief Interuptions Service Routine that handles interrupts in
 * the program
 * where there is an interrupt all delay counters are incremented
 * part of the code is from LAB3
 */
void user_isr(void);

/**
    reads BTN 1,2,3,4 status
    returns a value with ON/OFF status of buttons at
    4 least significant bits
    code taken from LAB 3
*/
int getbtns (void);

/** 
    reads switch 1,2,3,4 status
    returns a value with ON/OFF status of switches at
    4 least significant bits
    code taken from LAB 3
*/
int getsw (void);

/**
 * @brief creats a millisecond accuracurate delay
 * 
 * @param ms milliseconds delay
 */
void accurate_delay (int ms);

/**
 * @brief initializes all delay variables
 * 
 */
void init_delays ();

/**
 * @brief checks delay variable assosciated with obstacle movement delay
 * if delay variable equals ms we have achieved desired delay
 * 
 * @param ms desired delay in milliseconds
 * @return int int 0 if false, 1 if true
 */
int check_obstacle_delay (int ms);

/**
 * @brief checks delay variable assosciated with player movement delay
 * if delay variable equals ms we have achieved desired delay
 * @param ms desired delay in milliseconds
 * @return int 0 if false, 1 if true
 */
int check_player_delay (int ms);

/**
 * @brief checks the obstacle generator delay
 * if delay value has been reached then an obstacle 
 * is to be generated
 * 
 * @param ms delay in milliseconds
 * @return int int 1 if reached delay, else false
 */
int check_generator_delay (int ms);

/**
 * @brief checks the up down movement delay for obst2
 * if delay has been reached obst2 is moved up or down
 * lower delay requirement ==> faster up down movement
 * 
 * @param ms delay in milliseconds
 * @return int 1 if reached delay, else false
 */
int check_obst2_delay (int ms);

/**
 * @brief controls how fast obst0 boosts
 * lower delay value ==> faster boost
 * 
 * @param ms delay value in milliseconds
 */
void set_obst0_boost_delay (int ms);

/**
 * @brief checks if boost delay counter has reached
 * enough counts to boost obst0
 * 
 * @return int 1 if true else 0
 */
int check_obst0_boost_delay ();

/**
 * @brief checks the up down movement delay for obst0
 * if delay has been reached obst0 is moved up or down
 * lower delay requirement ==> faster up down movement
 * 
 * @param ms delay in milliseconds
 * @return int 1 if reached delay, else false
 */
int check_obst0_delay (int ms);

/**
    translates direction from button pushed
*/
char read_direction (int btn_stat);

/* game state */

/**
 * @brief initializes game_state struct
 * 
 */
void init_game_state ();

/**
 * @brief This function is called to increase the score
 * this function calls update_game_params
 * 
 */
void increase_score();

/**
 * @brief This function returns a string representation of the current score
 * 
 * @param score current score
 * @return char* string with current score
 */
char* score_string_gen (int score);


/* utility/helper functions */
void LED_debugger (int val);

/**
    function that returns a pseudorandom number in a range. 
    if range = N will return a number between [0,(N - 1)].
    Function utilizes a Linear congruent generator to generate 
    pseudorandom numbers.
*/
int random_number (int range);

/**
 * @brief returns pseudorandom between [0, range - 1]
 * has it's own seed
 * is used only for obstacle generation
 * 
 * @param range 
 * @return int the pseudorandom value
 */
int obstacle_gen_rand (int range);

/**
 * @brief returns pseudorandom number between [lower, upper]
 * 
 * @param lower lower range
 * @param upper upper range
 * @return int 
 */
int random_number_between (int lower, int upper);

/**
    Helper function that calculates powers of 2
    argument N will output 2^N
*/
uint8_t pow2 (uint8_t exponent);

