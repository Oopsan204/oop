#ifndef CHESS_H
#define CHESS_H

#include "Header.h"

class Chess
{
public:
    // Default constructor
    Chess();

    // Parameterized constructor
    Chess(int x, int y, int col, string src);

    // Function to move the chess piece to a new position
    virtual void move(int x, int y);

    // Function to simulate a move without updating the actual position
    virtual void fakeMove(int x, int y, int col);

    // Function to determine the possible moves for the piece
    virtual void canMove(int show);

    // Getter for the x-coordinate of the piece
    int getX();

    // Getter for the y-coordinate of the piece
    int getY();

    // Getter for the simulated x-coordinate of the piece
    int getFakeX();

    // Getter for the simulated y-coordinate of the piece
    int getFakeY();

    // Getter for the index of the piece
    int getIndex();

    // Function to reset the piece to its initial position
    void resetChess();

    // Function to log the move of the piece
    void makeLog(int beforeX, int beforeY);

    // Variable to store the color of the piece
    int color;

    // Variable to store the alive status of the piece
    bool alive = true;

    // Variable to store the simulated alive status of the piece
    bool fakeAlive = true;

    // Getter for the picture source of the piece
    string getPic();

protected:
    // Variable to store the name of the piece
    string name;

    // Variable to store the index of the piece
    int index;

    // Variable to store the picture source of the piece
    string pic;

    // Variables to store the current position of the piece
    int _x, _y;

    // Variables to store the simulated position of the piece
    int fakeX, fakeY;

    // Variables to store the initial position of the piece
    int firstX, firstY;

    // Variable to store the status of crossing the river
    bool crossRiver = false;
};

// Class for the King piece
class King : public Chess
{
public:
    // Default constructor
    King();

    // Parameterized constructor
    King(int x, int y, int col, string src);

    // Function to determine the possible moves for the King piece
    void canMove(int show);
};

// Class for the Advisor piece
class Advisor : public Chess
{
public:
    // Default constructor
    Advisor();

    // Parameterized constructor
    Advisor(int x, int y, int col, string src);

    // Function to determine the possible moves for the Advisor piece
    void canMove(int show);
};

// Class for the Minister piece
class Minister : public Chess
{
public:
    // Default constructor
    Minister();

    // Parameterized constructor
    Minister(int x, int y, int col, string src);

    // Function to determine the possible moves for the Minister piece
    void canMove(int show);
};

// Class for the Horse piece
class Horse : public Chess
{
public:
    // Default constructor
    Horse();

    // Parameterized constructor
    Horse(int x, int y, int col, string src);

    // Function to determine the possible moves for the Horse piece
    void canMove(int show);
};

// Class for the Soldier piece
class Soldier : public Chess
{
public:
    // Default constructor
    Soldier();

    // Parameterized constructor
    Soldier(int x, int y, int col, string src);

    // Function to determine the possible moves for the Soldier piece
    void canMove(int show);
};

// Class for the Chariot piece
class Chariot : public Chess
{
public:
    // Default constructor
    Chariot();

    // Parameterized constructor
    Chariot(int x, int y, int col, string src);

    // Function to determine the possible moves for the Chariot piece
    void canMove(int show);
};

// Class for the Cannon piece
class Cannon : public Chess
{
public:
    // Default constructor
    Cannon();

    // Parameterized constructor
    Cannon(int x, int y, int col, string src);

    // Function to determine the possible moves for the Cannon piece
    void canMove(int show);

private:
    // Variable to check if there is a block (skip)
    bool skip = false;
};

#endif // CHESS_H
