#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Header.h"
#include "viewer.h"
#include "Chess.h"
#include "Board.h"

class GameManager
{
public:
    // Constructor for the GameManager class
    GameManager();

    // Function to show the menu
    void showMenu();

    // Function to restart the game
    static void restartGame();

    // Function to load a game from a file
    static void loadFile(string path);

    // Function to write a log entry to the log file
    static void writeLog(string log);

    // Function to add a chess piece to the game
    void pushIn(Chess* ch);

    // Variable to store the current player
    static int currentPlayer;

    // Function to check if both kings are still alive
    static bool checkKing();

    // Function to check if a king is in check
    static bool isCheck(int flag); // flag 1: actual check, 0: simulated check

    // Function to simulate an AI move
    static void aiGame();

    // Function to check for stalemate
    static bool stalemate();

private:
    // Vector to store all chess pieces currently on the board
    vector<Chess*> onBoard;

    // Instance of the Board class
    Board b;

    // Instance of the Viewer class
    Viewer v;
};

#endif // GAMEMANAGER_H
