#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <Windows.h>

using namespace std;

// ��������� ��� ������ � ������� �������
const int BOARD_SIZE = 5;
const int NUM_SHIPS = 2;

// ���� ������������� �������� ����
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

// ���� ������������� ������
class Player {
public:
    string name;
    Board board;
    int numShips;

    Player(string n) : name(n), numShips(NUM_SHIPS) {}

    // ����� ��� ��������� ������� �� ��� ������
    void placeShips() {
        cout << name << ", �������� ���� ������ �� ���." << endl;
        for (int i = 0; i < numShips; ++i) {
            int x, y;
            cout << "������ ���������� ��� ������� " << i + 1 << " (x y): " << endl << "x:";
            cin >> x;
            cout << "y:";
            cin >> y;
            // �������� ���������� �������� ���������
            if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board.grid[x][y] != ' ') {
                cout << "��������� ����������. ��������� �� ���." << endl;
                --i;
                continue;
            }
            board.grid[x][y] = 'S';
        }
        cout << "������ �������� ������!" << endl;
    }

    // ����� ��� ��������� ���� ������
    void makeMove(Board& opponentBoard) {
        int x, y;
        cout << "������ ���������� ��� ������ ���� (x y): " << endl << "x:";
        cin >> x;
        cout << "y:";
        cin >> y;
        // �������� ���������� �������� ���������
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || opponentBoard.grid[x][y] == 'X' || opponentBoard.grid[x][y] == 'O') {
            cout << "��������� ����������. ��������� �� ���." << endl;
            makeMove(opponentBoard); // ����������� ������, ���� ������� ��������� ����������
            return;
        }
        if (opponentBoard.grid[x][y] == 'S') {
            cout << "��������!" << endl;
            opponentBoard.grid[x][y] = 'X'; // ���������� ���������
        }
        else {
            cout << "������!" << endl;
            opponentBoard.grid[x][y] = 'O'; // ���������� �������
        }
    }
};

// ������� ��� ��������� ������� ����'������
void placeComputerShips(Board& computerBoard) {
    srand(time(nullptr)); // ����������� ���������� ���������� �����
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

// ������� ��� ��������� ���� ����'�����
void computerMove(Board& playerBoard) {
    srand(time(nullptr)); // ����������� ���������� ���������� �����
    int x = rand() % BOARD_SIZE;
    int y = rand() % BOARD_SIZE;
    if (playerBoard.grid[x][y] == 'S') {
        cout << "����'���� ������ �� ����������� (" << x << ", " << y << ")!" << endl;
        playerBoard.grid[x][y] = 'X'; // ���������� ���������
    }
    else {
        cout << "����'���� ����������� �� ����������� (" << x << ", " << y << ")!" << endl;
        //playerBoard.grid[x][y] = 'O'; // ���������� �������
    }
}

// ������� ��� �������� ����� ���
bool checkGameStatus(Board& board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board.grid[i][j] == 'S') {
                return false; // ���� �� ���������� ���������� ������, ��� �� ��������
            }
        }
    }
    return true; // ���� �� ������ ��������, ��� ��������
}

int main() {

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    

    // ����������� ������
    Player player("�������");

    // ����������� �������� ���� ������ �� ����'�����
    Board playerBoard;
    Board computerBoard;

    // ��������� ������� �������
    player.placeShips();

    // ��������� ������� ����'������
    placeComputerShips(computerBoard);

    // ��� �����, ���� ������� ��� ����'���� ����� ���������� ������
    while (!checkGameStatus(player.board) && !checkGameStatus(computerBoard)) {
        // ճ� ������
        cout << "ճ� ������:" << endl;
        player.makeMove(computerBoard);
        if (checkGameStatus(computerBoard)) {
            cout << "³����! �� ������� �� ������ ������!" << endl;
            break;
        }

        // ճ� ����'�����
        cout << "ճ� ����'�����:" << endl;
        computerMove(computerBoard);
        if (checkGameStatus(computerBoard)) {
            cout << "����'���� ������ �� ���� ������! ��� ��������!" << endl;
            break;
        }
    }

    return 0;
}
