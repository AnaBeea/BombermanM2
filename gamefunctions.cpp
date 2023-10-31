#ifndef game_functions
#define game_functions
#include "bomb.cpp"
#include "player.cpp"
#include "enemy.cpp"
#include "gamecontroler.cpp"
using namespace std;

const int MAP_HEIGHT = 10;
const int MAP_WIDTH = 20;

const int EMPTY = 0;
const int STRONG_WALL = 1;
const int WEAK_WALL = 2;
const int BOMBERMAN = 3;
const int ENEMY = 4;
const int BOMB = 5;
const int EXPLOSION_AREA = 6;
const int UPGRADE_BOMB = 9;
const int UPGRADE_WALK = 11;

bool is_place_empty(int pos) {
    return (pos == 0);
}

bool is_place_upgrade(int pos) {
    if (pos == 9 || pos == 11) {
        return true;
    }
    return false;
}

template <typename T>
bool check_if_contain(const T* array, int size, T value) {
    for (int i = 0; i < size; ++i) {
        if (array[i] == value) {
            return 1;
        }
    }
    return 0;
}

void save_game(int map[MAP_HEIGHT][MAP_WIDTH])
{
    fstream game_data;
    game_data.open("game_data.txt");

    if (game_data.is_open())
    {
        //Salva array do jogo
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                game_data << map[i][j] << " ";
            }
            game_data << "\n";
        }
        game_data.close();

    }
    else
    {
        cout << "Falha em abrir o arquivo";
    }
}



void parar_cursor_piscar() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void reposicionar_cursor_inicio() {
    short int CX = 0, CY = 0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setup_cursor() {
    parar_cursor_piscar();
    reposicionar_cursor_inicio();
}
void show_menu() {

    cout << "=== DESENVOLVEDORES ===" << endl;
    cout << "Ana Beatriz da Conceicao, Karin Araldi e Lucas Vieira da Silva";
    cout << "=== MENU ===" << endl;
    cout << "1. Novo Jogo" << endl;
    cout << "2. Continuar" << endl;
    cout << "3. Carregar" << endl;
    cout << "4. Salvar" << endl;
    cout << "5. Sair" << endl;
    cout << "=============" << endl;
    cout << "Escolha uma opcao: ";
}

void load_game(int map[MAP_HEIGHT][MAP_WIDTH])
{
    fstream game_data;
    game_data.open("game_data.txt");

    if (game_data.is_open())
    {
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                game_data >> map[i][j];
            }
        }

        game_data.close();
    }
    else
    {
        cout << "Falha em abrir o arquivo";
        exit(1);
    }
}
#endif