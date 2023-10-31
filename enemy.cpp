#ifndef enemySTRUC
#define enemySTRUC

#include "bomb.cpp"
#include "player.cpp"
#include "gamecontroler.cpp"
#include "gamefunctions.cpp"


struct Enemy {
    int x, y;
    bool alive = true;

    void move(int map[MAP_HEIGHT][MAP_WIDTH]) {
        int possibleMoves[4] = { 1, 2, 3, 4 }; // 1: Up, 2: Down, 3: Left, 4: Right
        int numMoves = 4;

        // Check and remove invalid moves from possible moves
        if (map[y - 1][x] != 0 && map[y - 1][x] != 3) {
            numMoves--;
            possibleMoves[0] = 0; // Remove Up
        }
        if (map[y + 1][x] != 0 && map[y + 1][x] != 3) {
            numMoves--;
            possibleMoves[1] = 0; // Remove Down
        }
        if (map[y][x - 1] != 0 && map[y][x - 1] != 3) {
            numMoves--;
            possibleMoves[2] = 0; // Remove Left
        }
        if (map[y][x + 1] != 0 && map[y][x + 1] != 3) {
            numMoves--;
            possibleMoves[3] = 0; // Remove Right
        }

        // If there are valid moves, choose one randomly and move
        if (numMoves > 0) {
            int randomMoveIndex;
            do {
                randomMoveIndex = rand() % 4;
            } while (possibleMoves[randomMoveIndex] == 0);

            switch (possibleMoves[randomMoveIndex]) {
            case 1: // Up
                map[y][x] = 0;
                y--;
                break;
            case 2: // Down
                map[y][x] = 0;
                y++;
                break;
            case 3: // Left
                map[y][x] = 0;
                x--;
                break;
            case 4: // Right
                map[y][x] = 0;
                x++;
                break;
            }
            map[y][x] = 4;
        }
    }

    void show() {
        cout << char(206); // Enemy representation
    }

    void die(int map[MAP_HEIGHT][MAP_WIDTH]) {
        alive = false;
        map[y][x] = 0;
    }
};
#endif
