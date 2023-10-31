#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include "bomb.cpp"
#include "player.cpp"
#include "enemy.cpp"
#include "gamecontroler.cpp"
#include "gamefunctions.cpp"


void handle_input(Player& player, int map[MAP_HEIGHT][MAP_WIDTH], Bomb& bomb, GameControler& game_control, clock_t& game_time) {
    char keyboard_input;
    if (_kbhit()) {
        keyboard_input = _getch();
        if (keyboard_input == 'w' || keyboard_input == 'a' || keyboard_input == 's' || keyboard_input == 'd') {
            player.move(keyboard_input, map, bomb);
        }
        else if (keyboard_input == 'b' && bomb.is_placed == false && bomb.is_animating == false) {
            bomb.setup(player.x, player.y, map);
        }
        else if (keyboard_input == 'p') {
            game_control.pause_game(game_time);
        }
        else if (keyboard_input == 'f')
        {
            save_game(map);
        }

    }
}
void update_map(int map[MAP_HEIGHT][MAP_WIDTH], Player& player) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x] == 1) {
                cout << char(219);
            }
            else if (map[y][x] == 2) {
                cout << char(177);
            }
            else if (y == player.y && x == player.x) {
                player.show();
            }
            else if (map[y][x] == 5) {
                cout << char(190);
            }
            else if (map[y][x] == 6) {
                cout << char(216);
            }
            else if (map[y][x] == 4) {
                cout << char(206);
            }
            else if (map[y][x] == 9) {
                cout << char(207);
            }
            else if (map[y][x] == 11) {
                cout << char(208);
            }
            else {
                cout << " ";
            }
        }
        cout << "\n";
    }
}
void move_enemies(int map[MAP_HEIGHT][MAP_WIDTH], Enemy enemies[], int numEnemies) {
    for (int i = 0; i < numEnemies; ++i) {
        if (enemies[i].alive) {
            enemies[i].move(map);
        }
    }
}

bool check_game_over(int map[MAP_HEIGHT][MAP_WIDTH], Player& player) {
    bool is_end = player.alive;
    int num_of_enemies = 0;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x] == 4) {
                num_of_enemies++;
                if (player.x == x && player.y == y) {
                    is_end = false;
                }
            }
        }
    }
    if (num_of_enemies == 0) {
        is_end = false;
    }
    return is_end;
}
int main() {
    Player player;
    player.x = 1;
    player.y = 1;
    clock_t start, end, run_time, end_time;
    int time_before_pause = 0, all_time = 0;
    Bomb bomb;
    GameControler game_control;

    //int map[MAP_HEIGHT][MAP_WIDTH];
    int map[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1},
        {1, 2, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 2, 0, 1},
        {1, 9, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 1, 0, 2, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 2, 1, 0, 1},
        {1, 0, 2, 2, 0, 0, 2, 2, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 2, 0, 0, 1, 0, 2, 0, 1, 0, 0, 11, 0, 0, 1, 0, 2, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    start = clock();
    run_time = clock();
    int num_of_enemies = 3;
    Enemy enemies[3];

    enemies[0].x = 6;
    enemies[0].y = 4;
    enemies[1].x = 8;
    enemies[1].y = 8;
    enemies[2].x = 13;
    enemies[2].y = 2;

    map[4][6] = ENEMY;
    map[8][8] = ENEMY;
    map[2][13] = ENEMY;

    bool gameRunning = true;
    bool inMenu = false;
    int choice;
    while (gameRunning) {
        end = clock();
        if ((end - start) / CLOCKS_PER_SEC == 3) {
            move_enemies(map, enemies, 3);
            start = clock();
        }
        if (bomb.is_placed) {
            bomb.bomb_explode_controler(map, player, enemies, num_of_enemies);
        }
        else if (bomb.is_animating) {
            bomb.bomb_animate(map);
        }
        setup_cursor();
        handle_input(player, map, bomb, game_control, run_time);
        update_map(map, player);
        cout << "X[" << player.x << "] ";
        cout << "Y[" << player.y << "]" << endl;
        end_time = clock();
        game_control.run_time = time_before_pause + (end_time - run_time) / CLOCKS_PER_SEC;
        cout << "Tempo: " << game_control.run_time;
        gameRunning = check_game_over(map, player);

        while (game_control.is_menu) {
            time_before_pause = all_time;
            system("cls");
            setup_cursor();
            show_menu();
            cin >> choice;

            switch (choice) {
            case 1: // Novo Jogo
                player.x = 1;
                player.y = 1;
                player.alive = true;

                for (int y = 0; y < MAP_HEIGHT; y++) {
                    for (int x = 0; x < MAP_WIDTH; x++) {
                        map[y][x] = (rand() % 2) + 1;
                    }
                }

                enemies[0].x = 6;
                enemies[0].y = 4;
                enemies[0].alive = true;



                bomb.is_placed = false;
                bomb.is_animating = false;
                start = clock();
                gameRunning = true;
                break;
            case 2:
                game_control.unpause_game();
                start = clock();
                break;
            case 3:
                // Implemente a lógica para carregar um jogo aqui
                //load_game(map);
                break;
            case 4:
                if (gameRunning) {
                    // Implemente a lógica para salvar o jogo aqui
                }
                else {
                    cout << "Nenhum jogo em andamento para salvar." << endl;
                }
                break;
            case 5:
                inMenu = false;
                exit(1);
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
            }
        }

    }

    return 0;
}
