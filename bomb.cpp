#ifndef bombSTRUC
#define bombSTRUC
#include "player.cpp"
#include "enemy.cpp"
#include "gamecontroler.cpp"
#include "gamefunctions.cpp"

struct Bomb {
    bool is_placed = false;
    bool is_animating = false;
    bool is_upgrade = false;
    int x, y;
    clock_t start, end;
    int explode_cd_time = 3;
    int enemies;

    void setup(int px, int py, int map[MAP_HEIGHT][MAP_WIDTH]) {
        x = px;
        y = py;
        bomb_set_active();
        map[y][x] = 5;
    }

    void bomb_set_active() {
        start = clock();
        is_placed = true;
    }

    void modify_map(int map[MAP_HEIGHT][MAP_WIDTH], int num) {
        int positions[9] = { map[y][x - 1] ,map[y][x + 1], map[y - 1][x], map[y + 1][x], map[y][x], map[y][x - 2], map[y][x + 2], map[y - 2][x], map[y + 2][x] };
        int positions_index[9][2] = { {y, x - 1} ,{y, x + 1}, {y - 1,x}, {y + 1,x}, {y,x}, {y, x - 2},{y, x + 2}, {y - 2,x}, {y + 2,x} };
        int arr_size = 5;
        if (is_upgrade) {
            arr_size = 9;
        }
        for (int i = 0; i < arr_size; i++) {
            if (is_place_empty(positions[i]) || positions[i] == 6) {
                map[positions_index[i][0]][positions_index[i][1]] = num;
            }
        }
        map[y][x] = num;
    }

    void bomb_animate(int map[MAP_HEIGHT][MAP_WIDTH]) {
        end = clock();
        if ((end - start) / CLOCKS_PER_SEC == 1) {
            modify_map(map, 0);
            is_animating = false;
            if (is_upgrade) {
                is_upgrade = false;
            }
        }
    }
    void bomb_check_coll(int map[MAP_HEIGHT][MAP_WIDTH], Player& player, Enemy enemies[], int numEnemies) {
        int positions[9][2] = { {y, x - 1} ,{y, x + 1}, {y - 1,x}, {y + 1,x}, {y,x}, {y, x - 2},{y, x + 2}, {y - 2,x}, {y + 2,x} };
        int arr_size = 5;
        if (is_upgrade) {
            arr_size = 9;
        }
        for (int i = 0; i < arr_size; i++) {
            int y = positions[i][0];
            int x = positions[i][1];
            if (player.x == x && player.y == y) {
                player.die();
                return;
            }
            for (int i = 0; i < numEnemies; ++i) {
                if (enemies[i].x == x && enemies[i].y == y) {
                    enemies[i].die(map);
                }
            }
            if (map[y][x] == WEAK_WALL) {
                map[y][x] = 0;
            }
        }
    }

    void bomb_explode(int map[MAP_HEIGHT][MAP_WIDTH], Player& player, Enemy enemies[], int numEnemies) {
        bomb_check_coll(map, player, enemies, numEnemies);
        modify_map(map, 6);
        is_animating = true;
    }

    void bomb_explode_controler(int map[MAP_HEIGHT][MAP_WIDTH], Player& player, Enemy enemies[], int numEnemies) {
        end = clock();
        if ((end - start) / CLOCKS_PER_SEC == explode_cd_time) {
            is_placed = false;
            start = clock();
            bomb_explode(map, player, enemies, numEnemies);
        }
    }
};
#endif
