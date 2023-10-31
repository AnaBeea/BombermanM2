
#ifndef game_controler_STRUC
#define game_controler_STRUC

#include "bomb.cpp"
#include "player.cpp"
#include "enemy.cpp"
#include "gamefunctions.cpp"

struct GameControler {
    bool is_pause = false;
    bool game_end = false;
    bool is_menu = false;
    int run_time = 0;
    clock_t time_before_pause = 0; // Variável para armazenar o tempo antes da pausa
    clock_t time_paused = 0;
    void pause_game(clock_t& game_time) {
        is_pause = true;
        is_menu = true;
    }
    void unpause_game() {
        is_pause = false;
        is_menu = false;
    }
};
#endif
