#pragma once
#include "Header.h"
#include "Chess.h"

class Board
{
public:
    // Vector to store all chess pieces currently on the board
    static vector<Chess*> onBoard;

    // 2D arrays to represent the board state, possible moves, and virtual moves
    static int board[9][10];
    static int move[9][10];
    static int virtualMove[9][10];

    // Function to add a chess piece to the board
    static void pushIn(Chess*);

    // Function to print the current state of the board
    static void printBoard();

    // Function to reset the board to its initial state
    static void resetBoard();

    // Function to clear the move array
    static void clearMove();

    // Function to print the current state of the move array
    static void printMove();

    // Function to clear the virtual move array
    static void clearVirtualMove();

    // Function to print the current state of the virtual move array
    static void printVirtualMove();

    // Pointers to the red and black kings on the board
    static Chess* RKing;
    static Chess* BKing;
};

