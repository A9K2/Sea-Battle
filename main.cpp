#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <Windows.h>

using namespace std;

// Константи для розмірів і кількості кораблів
const int BOARD_SIZE = 5;
const int NUM_SHIPS = 2;

// Клас представлення ігрового поля
class Board {
public:
    vector<vector<char>> grid;

    Board() {
        grid = vector<vector<char>>(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));
    }

    void printBoard() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// Клас представлення гравця
class Player {
public:
    string name;
    Board board;
    int numShips;

    Player(string n) : name(n), numShips(NUM_SHIPS) {}

    // Метод для розміщення кораблів на полі гравця
    void placeShips() {
        cout << name << ", розмістіть ваші кораблі на полі." << endl;
        for (int i = 0; i < numShips; ++i) {
            int x, y;
            cout << "Введіть координати для корабля " << i + 1 << " (x y): " << endl << "x:";
            cin >> x;
            cout << "y:";
            cin >> y;
            // Перевірка коректності введених координат
            if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board.grid[x][y] != ' ') {
                cout << "Некоректні координати. Спробуйте ще раз." << endl;
                --i;
                continue;
            }
            board.grid[x][y] = 'S';
        }
        cout << "Кораблі розміщено успішно!" << endl;
    }

    // Метод для виконання ходу гравця
    void makeMove(Board& opponentBoard) {
        int x, y;
        cout << "Введіть координати для вашого ходу (x y): " << endl << "x:";
        cin >> x;
        cout << "y:";
        cin >> y;
        // Перевірка коректності введених координат
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || opponentBoard.grid[x][y] == 'X' || opponentBoard.grid[x][y] == 'O') {
            cout << "Некоректні координати. Спробуйте ще раз." << endl;
            makeMove(opponentBoard); // Рекурсивний виклик, якщо введено некоректні координати
            return;
        }
        if (opponentBoard.grid[x][y] == 'S') {
            cout << "Влучання!" << endl;
            opponentBoard.grid[x][y] = 'X'; // Позначення попадання
        }
        else {
            cout << "Промах!" << endl;
            opponentBoard.grid[x][y] = 'O'; // Позначення промаху
        }
    }
};

// Функція для розміщення кораблів комп'ютером
void placeComputerShips(Board& computerBoard) {
    srand(time(nullptr)); // Ініціалізація генератора випадкових чисел
    for (int i = 0; i < NUM_SHIPS; ++i) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        if (computerBoard.grid[x][y] == ' ') {
            computerBoard.grid[x][y] = 'S';
        }
        else {
            --i;
        }
    }
}

// Функція для виконання ходу комп'ютера
void computerMove(Board& playerBoard) {
    srand(time(nullptr)); // Ініціалізація генератора випадкових чисел
    int x = rand() % BOARD_SIZE;
    int y = rand() % BOARD_SIZE;
    if (playerBoard.grid[x][y] == 'S') {
        cout << "Комп'ютер вразив по координатах (" << x << ", " << y << ")!" << endl;
        playerBoard.grid[x][y] = 'X'; // Позначення попадання
    }
    else {
        cout << "Комп'ютер промахнувся по координатах (" << x << ", " << y << ")!" << endl;
        //playerBoard.grid[x][y] = 'O'; // Позначення промаху
    }
}

// Функція для перевірки стану гри
bool checkGameStatus(Board& board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board.grid[i][j] == 'S') {
                return false; // Якщо ще залишилися непотоплені кораблі, гра не закінчена
            }
        }
    }
    return true; // Якщо всі кораблі потоплені, гра закінчена
}

int main() {

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    

    // Ініціалізація гравця
    Player player("Гравець");

    // Ініціалізація ігрового поля гравця та комп'ютера
    Board playerBoard;
    Board computerBoard;

    // Розміщення кораблів гравцем
    player.placeShips();

    // Розміщення кораблів комп'ютером
    placeComputerShips(computerBoard);

    // Гра триває, поки гравець або комп'ютер мають непотоплені кораблі
    while (!checkGameStatus(player.board) && !checkGameStatus(computerBoard)) {
        // Хід гравця
        cout << "Хід гравця:" << endl;
        player.makeMove(computerBoard);
        if (checkGameStatus(computerBoard)) {
            cout << "Вітаємо! Ви знищили всі кораблі ворога!" << endl;
            break;
        }

        // Хід комп'ютера
        cout << "Хід комп'ютера:" << endl;
        computerMove(computerBoard);
        if (checkGameStatus(computerBoard)) {
            cout << "Комп'ютер знищив всі ваші кораблі! Гра закінчена!" << endl;
            break;
        }
    }

    return 0;
}
