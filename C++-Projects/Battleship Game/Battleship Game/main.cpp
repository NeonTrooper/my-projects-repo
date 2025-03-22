#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Ship.h"

const int BOARD_SIZE = 8;

void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = '~';
        }
    }
}

void printBoard(char board[BOARD_SIZE][BOARD_SIZE], bool showShips = false) {
    std::cout << "  A B C D E F G H" << std::endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (showShips && board[i][j] == 'S') {
                std::cout << 'S' << " ";
            } else {
                std::cout << board[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

bool placeShip(char board[BOARD_SIZE][BOARD_SIZE], Ship& ship, char orientation) {
    int x = ship.getX();
    int y = ship.getY();
    unsigned size = ship.getSize();

    if (orientation == 'H' || orientation == 'h') {
        if (x + size > BOARD_SIZE) return false;
        for (int i = 0; i < size; ++i) {
            if (board[y][x + i] != '~') return false;
        }
        for (int i = 0; i < size; ++i) {
            board[y][x + i] = 'S';
        }
    } else if (orientation == 'V' || orientation == 'v') {
        if (y + size > BOARD_SIZE) return false;
        for (int i = 0; i < size; ++i) {
            if (board[y + i][x] != '~') return false;
        }
        for (int i = 0; i < size; ++i) {
            board[y + i][x] = 'S';
        }
    } else {
        return false;
    }
    return true;
}

bool attack(char board[BOARD_SIZE][BOARD_SIZE], int x, int y, std::vector<Ship>& ships) {
    if (board[y][x] == 'S') {
        board[y][x] = 'X';
        for (Ship& ship : ships) {
            if (ship.checkHit(x, y)) {
                ship.setAlive(false);
                std::cout << "Hit! " << ship.getType() << " is hit!" << std::endl;
                if (!ship.isAlive()) {
                    std::cout << "Ship " << ship.getType() << " has been sunk!" << std::endl;
                }
                return true;
            }
        }
    } else {
        board[y][x] = 'O';
        std::cout << "Miss!" << std::endl;
    }
    return false;
}

int main() {
    srand(time(0));

    // Εμφάνιση μενού επιλογής
    int choice;
    std::cout << "Welcome to Battleship!" << std::endl;
    std::cout << "1. Play against the computer" << std::endl;
    std::cout << "2. Play against another player" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice != 1 && choice != 2) {
        std::cout << "Invalid choice. Exiting..." << std::endl;
        return 0; // Τερματισμός του προγράμματος αν η επιλογή δεν είναι έγκυρη
    }

    // Προετοιμασία πινάκων
    char player1Board[BOARD_SIZE][BOARD_SIZE];
    char player2Board[BOARD_SIZE][BOARD_SIZE];
    char player1AttackBoard[BOARD_SIZE][BOARD_SIZE];
    char player2AttackBoard[BOARD_SIZE][BOARD_SIZE];

    initializeBoard(player1Board);
    initializeBoard(player2Board);
    initializeBoard(player1AttackBoard);
    initializeBoard(player2AttackBoard);

    std::vector<Ship> player1Ships;
    std::vector<Ship> player2Ships;

    // Προσθήκη πλοίων στον παίκτη 1
    player1Ships.push_back(Ship("Carrier", 6, 0, 0));
    player1Ships.push_back(Ship("Battleship", 5, 0, 1));
    player1Ships.push_back(Ship("Submarine", 4, 0, 2));
    player1Ships.push_back(Ship("Destroyer", 3, 0, 3));
    player1Ships.push_back(Ship("Cruiser", 3, 0, 4));
    player1Ships.push_back(Ship("Patrol Boat", 2, 0, 5));

    // Προσθήκη πλοίων στον παίκτη 2
    player2Ships.push_back(Ship("Carrier", 6, 0, 0));
    player2Ships.push_back(Ship("Battleship", 5, 0, 1));
    player2Ships.push_back(Ship("Submarine", 4, 0, 2));
    player2Ships.push_back(Ship("Destroyer", 3, 0, 3));
    player2Ships.push_back(Ship("Cruiser", 3, 0, 4));
    player2Ships.push_back(Ship("Patrol Boat", 2, 0, 5));

    // Τοποθέτηση πλοίων στον πίνακα του παίκτη 1
    for (Ship& ship : player1Ships) {
        int x, y;
        char orientation;
        std::cout << "Player 1, place your " << ship.getType() << " (size " << ship.getSize() << "): ";
        std::cin >> x >> y >> orientation;
        while (!placeShip(player1Board, ship, orientation)) {
            std::cout << "Invalid position or orientation. Try again: ";
            std::cin >> x >> y >> orientation;
        }
    }

    // Τοποθέτηση πλοίων στον πίνακα του παίκτη 2
    if (choice == 2) {
        for (Ship& ship : player2Ships) {
            int x, y;
            char orientation;
            std::cout << "Player 2, place your " << ship.getType() << " (size " << ship.getSize() << "): ";
            std::cin >> x >> y >> orientation;
            while (!placeShip(player2Board, ship, orientation)) {
                std::cout << "Invalid position or orientation. Try again: ";
                std::cin >> x >> y >> orientation;
            }
        }
    } else {
        // Αυτόματη τοποθέτηση πλοίων για τον υπολογιστή (Player 2)
        for (Ship& ship : player2Ships) {
            int x = rand() % BOARD_SIZE;
            int y = rand() % BOARD_SIZE;
            char orientation = (rand() % 2 == 0) ? 'H' : 'V';
            while (!placeShip(player2Board, ship, orientation)) {
                x = rand() % BOARD_SIZE;
                y = rand() % BOARD_SIZE;
                orientation = (rand() % 2 == 0) ? 'H' : 'V';
            }
        }
    }

    bool player1Turn = true;
    bool gameOver = false;

    while (!gameOver) {
        if (player1Turn) {
            std::cout << "Player 1's turn to attack!" << std::endl;
            printBoard(player1AttackBoard);
            int x, y;
            std::cout << "Enter coordinates to attack (x y): ";
            std::cin >> x >> y;
            if (attack(player2Board, x, y, player2Ships)) {
                player1AttackBoard[y][x] = 'X';
            } else {
                player1AttackBoard[y][x] = 'O';
            }
            printBoard(player1AttackBoard);
        } else {
            if (choice == 2) {
                std::cout << "Player 2's turn to attack!" << std::endl;
                printBoard(player2AttackBoard);
                int x, y;
                std::cout << "Enter coordinates to attack (x y): ";
                std::cin >> x >> y;
                if (attack(player1Board, x, y, player1Ships)) {
                    player2AttackBoard[y][x] = 'X';
                } else {
                    player2AttackBoard[y][x] = 'O';
                }
                printBoard(player2AttackBoard);
            } else {
                // Επίθεση από τον υπολογιστή
                std::cout << "Computer's turn to attack!" << std::endl;
                int x = rand() % BOARD_SIZE;
                int y = rand() % BOARD_SIZE;
                std::cout << "Computer attacks: (" << x << ", " << y << ")" << std::endl;
                if (attack(player1Board, x, y, player1Ships)) {
                    player2AttackBoard[y][x] = 'X';
                } else {
                    player2AttackBoard[y][x] = 'O';
                }
                printBoard(player2AttackBoard);
            }
        }

        // Έλεγχος αν όλα τα πλοία του ενός παίκτη έχουν βυθιστεί
        bool player1AllSunk = true;
        for (Ship& ship : player1Ships) {
            if (ship.isAlive()) {
                player1AllSunk = false;
                break;
            }
        }

        bool player2AllSunk = true;
        for (Ship& ship : player2Ships) {
            if (ship.isAlive()) {
                player2AllSunk = false;
                break;
            }
        }

        if (player1AllSunk) {
            std::cout << "Player 2 wins! All Player 1 ships are sunk!" << std::endl;
            gameOver = true;
        } else if (player2AllSunk) {
            std::cout << "Player 1 wins! All Player 2 ships are sunk!" << std::endl;
            gameOver = true;
        }

        player1Turn = !player1Turn;
    }

    return 0;
}
