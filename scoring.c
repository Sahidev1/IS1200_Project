#include <pic32mx.h>
#include "game_header.h"

game_state game_state_;
int initial_up_down0, initial_up_down2, initial_live_delay;

void init_game_state (){
    game_state_.current_score = 0;
    game_state_.gen_delay = 5000;
    game_state_.obst0_up_down_delay = 100;
    game_state_.obst2_up_down_delay = 100;
    game_state_.live_obstacle_delay = 50;

    game_state_.player = ALIVE;

    initial_up_down0 = game_state_.obst0_up_down_delay;
    initial_up_down2 = game_state_.obst2_up_down_delay;
    initial_live_delay = game_state_.live_obstacle_delay;
}


void update_game_params (){
    int score = game_state_.current_score;
    int gen_delay = game_state_.gen_delay;
    int up_down0 = game_state_.obst0_up_down_delay;
    int up_down2 = game_state_.obst2_up_down_delay;
    int live_delay = game_state_.live_obstacle_delay;

    if (gen_delay > 4000){
        game_state_.gen_delay -= 100;
    }
    if (gen_delay <= 4000 && gen_delay > 3000){
        game_state_.gen_delay -= 50;
    }
    if (gen_delay <= 3000 && gen_delay > 1500){
        game_state_.gen_delay -= 25;
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

void increase_score (){
    game_state_.current_score++;
    update_game_params();
}

