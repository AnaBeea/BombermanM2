#ifndef playerSTRUC
#define playerSTRUC
#include "bomb.cpp"
#include "enemy.cpp"
#include "gamecontroler.cpp"
#include "gamefunctions.cpp"

struct Player {
    int x = 0, y = 0;
    bool alive = true;
    int walls_remain = 0;
    void show() {
        cout << char(169);
    }

    void die() {
        alive = false;
    }

    int check_if_move_result_dead(int pos) {
        if (pos == ENEMY || pos == EXPLOSION_AREA) {
            return 1;
        }
        return 0;
    }

    template <typename MY_BOMB>
    void move(char direction, int map[MAP_HEIGHT][MAP_WIDTH], MY_BOMB& bomb) {
        int positions[4] = { map[y + 1][x], map[y - 1][x], map[y][x - 1], map[y][x + 1] };
        switch (direction) {
        case 's': // Up
            if (check_if_move_result_dead(positions[0])) {
                alive = false;
                return;
            }
            if (is_place_empty(positions[0]) || is_place_upgrade(positions[0]) || walls_remain > 0) {
                y++;
                if (walls_remain > 0 && !is_place_empty(positions[0])) {
                    walls_remain--;
                }
            }
            if (positions[0] == UPGRADE_BOMB) {
                bomb.is_upgrade = true;
                map[y][x] = 0;
            }
            if (positions[0] == UPGRADE_WALK) {
                walls_remain = 2;
                map[y][x] = 0;
            }
            break;
        case 'w': // Down
            if (check_if_move_result_dead(positions[1])) {
                alive = false;
                return;
            }
            if (is_place_empty(positions[1]) || is_place_upgrade(positions[1]) || walls_remain > 0) {
                y--;
                if (walls_remain > 0 && !is_place_empty(positions[1])) {
                    walls_remain--;
                }
            }
            if (positions[1] == UPGRADE_BOMB) {
                bomb.is_upgrade = true;
                map[y][x] = 0;
            }
            if (positions[1] == UPGRADE_WALK) {
                walls_remain = 2;
                map[y][x] = 0;
            }
            break;
        case 'a': // Left
            if (check_if_move_result_dead(positions[2])) {
                alive = false;
                return;
            }
            if (is_place_empty(positions[2]) || is_place_upgrade(positions[2]) || walls_remain > 0) {
                x--;
                if (walls_remain > 0 && !is_place_empty(positions[2])) {
                    walls_remain--;
                }
            }
            if (positions[2] == UPGRADE_BOMB) {
                bomb.is_upgrade = true;
                map[y][x] = 0;
            }
            if (positions[2] == UPGRADE_WALK) {
                walls_remain = 2;
                map[y][x] = 0;
            }
            break;
        case 'd': // Right
            if (check_if_move_result_dead(positions[3])) {
                alive = false;
                return;
            }
            if (is_place_empty(positions[3]) || is_place_upgrade(positions[3]) || walls_remain > 0) {
                x++;
                if (walls_remain > 0 && !is_place_empty(positions[3])) {
                    walls_remain--;
                }
            }
            if (positions[3] == UPGRADE_BOMB) {
                bomb.is_upgrade = true;
                map[y][x] = 0;
            }
            if (positions[3] == UPGRADE_WALK) {
                walls_remain = 2;
                map[y][x] = 0;
            }
            break;
        }
    }
};
#endif
