#include <pic32mx.h>
#include "game_header.h"

game_state game_state_;
int initial_up_down0, initial_up_down2, initial_live_delay;
char score_string[14];

/**
 * @brief initializes game_state struct
 * 
 */
void init_game_state (){
    game_state_.current_score = 0;
    game_state_.gen_delay = 5000;
    game_state_.obst0_up_down_delay = 100;
    game_state_.obst2_up_down_delay = 100;
    game_state_.live_obstacle_delay = 50;

    game_state_.player_status = ALIVE;

    initial_up_down0 = game_state_.obst0_up_down_delay;
    initial_up_down2 = game_state_.obst2_up_down_delay;
    initial_live_delay = game_state_.live_obstacle_delay;
}

/**
 * @brief updates game_state parameters based on the score
 * 
 */
void update_game_params (){
    int score = game_state_.current_score;
    int gen_delay = game_state_.gen_delay;
    int up_down0 = game_state_.obst0_up_down_delay;
    int up_down2 = game_state_.obst2_up_down_delay;
    int live_delay = game_state_.live_obstacle_delay;

    if (gen_delay > 4000){
        game_state_.gen_delay -= 150;
    }
    if (gen_delay <= 4000 && gen_delay > 3000){
        game_state_.gen_delay -= 75;
    }
    if (gen_delay <= 3000 && gen_delay > 1500){
        game_state_.gen_delay -= 50;
    }

    if (up_down0 > 90){
        game_state_.obst0_up_down_delay = 
        initial_up_down0 - (score / 2);
    }
    if (up_down0 <= 90 && up_down0 > 80){
        game_state_.obst0_up_down_delay =
        initial_up_down0 - (score / 4);
    }

    if(up_down2 > 88){
        game_state_.obst2_up_down_delay =
        initial_up_down2 - (score / 2);
    }
    if (up_down2 <= 88 && up_down2 > 75){
        game_state_.obst2_up_down_delay =
        initial_up_down2 - (score / 3);
    }

    if (score > 40 && live_delay >= 30){
        game_state_.live_obstacle_delay =
        initial_live_delay - ((score - 40) / 2);
    }
}

/**
 * @brief This function is called to increase the score
 * this function calls update_game_params
 * 
 */
void increase_score (){
    game_state_.current_score++;
    update_game_params();
}

/**
 * @brief This function returns a string representation of the current score
 * 
 * @param score current score
 * @return char* string with current score
 */
char* score_string_gen (int score){
    score_string[0] = 'S';
    score_string[1] = 'c';
    score_string[2] = 'o';
    score_string[3] = 'r';
    score_string[4] = 'e';
    score_string[5] = ':';
    score_string[6] = 32;

    if (score >= 10000){
        score = 9999;
    }

    int i = 7;
    if (score > 0){
        int temparr[5] = {-1,-1,-1,-1,-1};
        int nr_digits = 0;
        while (score != 0 && nr_digits < 5){
            temparr[nr_digits++] = score % 10;
            score /= 10;
        }
        while (temparr[nr_digits] == -1)nr_digits--;
        int j;
        for (j = nr_digits; j >= 0; j--){
            score_string[i++] = 48 + temparr[j];
        }
    }
    else {
        score_string[7] = 48;
        score_string[8] = 0;
        return score_string;
    }
    score_string[i] = 0;
    return score_string;
}


