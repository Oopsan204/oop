#include "Chess.h"
#include "Board.h"
#include "GameManager.h"

// Default constructor for the Chess class
Chess::Chess()
{
    //name="Chess";
}

// Parameterized constructor for the Chess class
Chess::Chess(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    fakeX = x;
    fakeY = y;
}

// Function to move the chess piece to a new position
void Chess::move(int x, int y)
{
    // Check if the move is valid
    if (Board::move[x][y] == 1)
    {
        // Update the board and piece's position
        Board::board[_x][_y] = 0;
        _x = x;
        _y = y;
        if (color == 1)
            Board::board[x][y] = 1;
        else if (color == -1)
            Board::board[x][y] = -1;
        GameManager::currentPlayer++;
        fakeX = _x;
        fakeY = _y;
    }
    // Clear the move array after the move
    Board::clearMove();
}

// Function to simulate a move without updating the actual position
void Chess::fakeMove(int x, int y, int col)
{
    Board::board[fakeX][fakeY] = col;
    fakeX = x;
    fakeY = y;
    Board::board[fakeX][fakeY] = this->color;
}

// Getter for the x-coordinate of the piece
int Chess::getX() {
    return this->_x;
}

// Getter for the y-coordinate of the piece
int Chess::getY() {
    return this->_y;
}

// Getter for the simulated x-coordinate of the piece
int Chess::getFakeX()
{
    return fakeX;
}

// Getter for the simulated y-coordinate of the piece
int Chess::getFakeY()
{
    return fakeY;
}

// Getter for the index of the piece
int Chess::getIndex()
{
    return this->index;
}

// Function to reset the piece to its initial position
void Chess::resetChess()
{
    _x = firstX;
    _y = firstY;
    fakeX = firstX;
    fakeY = firstY;
    Board::board[_x][_y] = color;
    alive = true;
    fakeAlive = true;
}

// Function to log the move of the piece
void Chess::makeLog(int beforeX, int beforeY)
{
    string log;
    if (color == 1) {
        log = "Player: 1, Action: ";
    }
    else {
        log = "Player: 2, Action: ";
    }
    log = log + name + " (" + to_string(beforeX) +
        ", " + to_string(beforeY) + ") -> (" + to_string(_x) + ", " + to_string(_y) + ")\n";
    GameManager::writeLog(log);
}

// Function to determine the possible moves for the piece
void Chess::canMove(int show)
{
    Board::clearMove();
    if (_x - 1 >= 0) Board::move[_x - 1][_y] = 1;
    if (_x + 1 <= 8) Board::move[_x + 1][_y] = 1;
    if (_y - 1 >= 0) Board::move[_x][_y - 1] = 1;
    if (_y + 1 <= 9) Board::move[_x][_y + 1] = 1;
}

// Getter for the picture source of the piece
string Chess::getPic()
{
    return pic;
}

// Parameterized constructor for the King class
King::King(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    name = "King";
    fakeX = x;
    fakeY = y;
}

// Function to determine the possible moves for the King piece
void King::canMove(int show)
{
    int x, y;
    if (show == 0) // for actual moves
    {
        if (color == 1)
        {
            x = Board::BKing->getX();
            y = Board::BKing->getY();
            // Check if the move is valid
            if (x == _x)
            {
                bool haveBlock = false;
                for (int i = y + 1; i < _y; i++)
                {
                    if (Board::board[x][i] != 0)
                    {
                        haveBlock = true;
                    }
                }
                if (!haveBlock)
                {
                    Board::move[x][y] = 1;
                }
            }
            // Check other possible moves
            if (_x - 1 >= 3 && Board::board[_x - 1][_y] != 1)
            {
                Board::move[_x - 1][_y] = 1;
            }
            if (_x + 1 <= 5 && Board::board[_x + 1][_y] != 1)
            {
                Board::move[_x + 1][_y] = 1;
            }
            if (_y - 1 >= 7 && Board::board[_x][_y - 1] != 1)
            {
                Board::move[_x][_y - 1] = 1;
            }
            if (_y + 1 <= 9 && Board::board[_x][_y + 1] != 1)
            {
                Board::move[_x][_y + 1] = 1;
            }
        }
        else if (color == -1)
        {
            x = Board::RKing->getX();
            y = Board::RKing->getY();
            // Check if the move is valid
            if (x == _x)
            {
                bool haveBlock = false;
                for (int i = _y + 1; i < y; i++)
                {
                    if (Board::board[x][i] != 0)
                    {
                        haveBlock = true;
                    }
                }
                if (!haveBlock)
                {
                    Board::move[x][y] = 1;
                }
            }
            // Check other possible moves
            if (_x - 1 >= 3 && Board::board[_x - 1][_y] != -1)
            {
                Board::move[_x - 1][_y] = 1;
            }
            if (_x + 1 <= 5 && Board::board[_x + 1][_y] != -1)
            {
                Board::move[_x + 1][_y] = 1;
            }
            if (_y - 1 >= 0 && Board::board[_x][_y - 1] != -1)
            {
                Board::move[_x][_y - 1] = 1;
            }
            if (_y + 1 <= 2 && Board::board[_x][_y + 1] != -1)
            {
                Board::move[_x][_y + 1] = 1;
            }
        }
    }
    else // for virtual moves
    {
        if (color == 1)
        {
            x = Board::BKing->getFakeX();
            y = Board::BKing->getFakeY();
            // Check if the move is valid
            if (x == _x)
            {
                bool haveBlock = false;
                for (int i = y + 1; i < fakeY; i++)
                {
                    if (Board::board[x][i] != 0)
                    {
                        haveBlock = true;
                    }
                }
                if (!haveBlock)
                {
                    Board::virtualMove[x][y] = 1;
                }
            }
            // Check other possible moves
            if (fakeX - 1 >= 3 && Board::board[fakeX - 1][fakeY] != 1)
            {
                Board::virtualMove[fakeX - 1][fakeY] = 1;
            }
            if (fakeX + 1 <= 5 && Board::board[fakeX + 1][fakeY] != 1)
            {
                Board::virtualMove[fakeX + 1][fakeY] = 1;
            }
            if (fakeY - 1 >= 7 && Board::board[fakeX][fakeY - 1] != 1)
            {
                Board::virtualMove[fakeX][fakeY - 1] = 1;
            }
            if (fakeY + 1 <= 9 && Board::board[fakeX][fakeY + 1] != 1)
            {
                Board::virtualMove[fakeX][fakeY + 1] = 1;
            }
        }
        else if (color == -1)
        {
            x = Board::RKing->getX();
            y = Board::RKing->getY();
            // Check if the move is valid
            if (x == _x)
            {
                bool haveBlock = false;
                for (int i = fakeY + 1; i < y; i++)
                {
                    if (Board::board[x][i] != 0)
                    {
                        haveBlock = true;
                    }
                }
                if (!haveBlock)
                {
                    Board::virtualMove[x][y] = 1;
                }
            }
            // Check other possible moves
            if (fakeX - 1 >= 3 && Board::board[fakeX - 1][fakeY] != -1)
            {
                Board::virtualMove[fakeX - 1][fakeY] = 1;
            }
            if (fakeX + 1 <= 5 && Board::board[fakeX + 1][fakeY] != -1)
            {
                Board::virtualMove[fakeX + 1][fakeY] = 1;
            }
            if (fakeY - 1 >= 0 && Board::board[fakeX][fakeY - 1] != -1)
            {
                Board::virtualMove[fakeX][fakeY - 1] = 1;
            }
            if (fakeY + 1 <= 2 && Board::board[fakeX][fakeY + 1] != -1)
            {
                Board::virtualMove[fakeX][fakeY + 1] = 1;
            }
        }
    }
}

// Parameterized constructor for the Advisor class
Advisor::Advisor(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    name = "Advisor";
    fakeX = x;
    fakeY = y;
}

// Function to determine the possible moves for the Advisor piece
void Advisor::canMove(int show)
{
    if (show == 0) // for actual moves
    {
        if (color == 1)
        {
            // Check if the move is valid
            if (_x - 1 >= 3 && _y - 1 >= 7 && Board::board[_x - 1][_y - 1] != 1)
            {
                Board::move[_x - 1][_y - 1] = 1;
            }
            if (_x + 1 <= 5 && _y - 1 >= 7 && Board::board[_x + 1][_y - 1] != 1)
            {
                Board::move[_x + 1][_y - 1] = 1;
            }
            if (_x - 1 >= 3 && _y + 1 <= 9 && Board::board[_x - 1][_y + 1] != 1)
            {
                Board::move[_x - 1][_y + 1] = 1;
            }
            if (_x + 1 <= 5 && _y + 1 <= 9 && Board::board[_x + 1][_y + 1] != 1)
            {
                Board::move[_x + 1][_y + 1] = 1;
            }
        }
        else if (color == -1)
        {
            // Check if the move is valid
            if (_x - 1 >= 3 && _y - 1 >= 0 && Board::board[_x - 1][_y - 1] != -1)
            {
                Board::move[_x - 1][_y - 1] = 1;
            }
            if (_x + 1 <= 5 && _y - 1 >= 0 && Board::board[_x + 1][_y - 1] != -1)
            {
                Board::move[_x + 1][_y - 1] = 1;
            }
            if (_x - 1 >= 3 && _y + 1 <= 2 && Board::board[_x - 1][_y + 1] != -1)
            {
                Board::move[_x - 1][_y + 1] = 1;
            }
            if (_x + 1 <= 5 && _y + 1 <= 2 && Board::board[_x + 1][_y + 1] != -1)
            {
                Board::move[_x + 1][_y + 1] = 1;
            }
        }
    }
    else // for virtual moves
    {
        if (color == 1)
        {
            // Check if the move is valid
            if (fakeX - 1 >= 3 && fakeY - 1 >= 7 && Board::board[fakeX - 1][fakeY - 1] != 1)
            {
                Board::virtualMove[fakeX - 1][fakeY - 1] = 1;
            }
            if (fakeX + 1 <= 5 && fakeY - 1 >= 7 && Board::board[fakeX + 1][fakeY - 1] != 1)
            {
                Board::virtualMove[fakeX + 1][fakeY - 1] = 1;
            }
            if (fakeX - 1 >= 3 && fakeY + 1 <= 9 && Board::board[fakeX - 1][fakeY + 1] != 1)
            {
                Board::virtualMove[fakeX - 1][fakeY + 1] = 1;
            }
            if (fakeX + 1 <= 5 && fakeY + 1 <= 9 && Board::board[fakeX + 1][fakeY + 1] != 1)
            {
                Board::virtualMove[fakeX + 1][fakeY + 1] = 1;
            }
        }
        else if (color == -1)
        {
            // Check if the move is valid
            if (fakeX - 1 >= 3 && fakeY - 1 >= 0 && Board::board[fakeX - 1][fakeY - 1] != -1)
            {
                Board::virtualMove[fakeX - 1][fakeY - 1] = 1;
            }
            if (fakeX + 1 <= 5 && fakeY - 1 >= 0 && Board::board[fakeX + 1][fakeY - 1] != -1)
            {
                Board::virtualMove[fakeX + 1][fakeY - 1] = 1;
            }
            if (fakeX - 1 >= 3 && fakeY + 1 <= 2 && Board::board[fakeX - 1][fakeY + 1] != -1)
            {
                Board::virtualMove[fakeX - 1][fakeY + 1] = 1;
            }
            if (fakeX + 1 <= 5 && fakeY + 1 <= 2 && Board::board[fakeX + 1][fakeY + 1] != -1)
            {
                Board::virtualMove[fakeX + 1][fakeY + 1] = 1;
            }
        }
    }
}

// Parameterized constructor for the Minister class
Minister::Minister(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    name = "Minister";
    fakeX = x;
    fakeY = y;
}

// Function to determine the possible moves for the Minister piece
void Minister::canMove(int show)
{
    if (show == 0) // for actual moves
    {
        if (color == 1)
        {
            // Check if the move is valid
            if (_x - 2 >= 0 && _y - 2 >= 5 && Board::board[_x - 1][_y - 1] == 0 && Board::board[_x - 2][_y - 2] != 1)
            {
                Board::move[_x - 2][_y - 2] = 1;
            }
            if (_x + 2 <= 8 && _y - 2 >= 5 && Board::board[_x + 1][_y - 1] == 0 && Board::board[_x + 2][_y - 2] != 1)
            {
                Board::move[_x + 2][_y - 2] = 1;
            }
            if (_x - 2 >= 0 && _y + 2 <= 9 && Board::board[_x - 1][_y + 1] == 0 && Board::board[_x - 2][_y + 2] != 1)
            {
                Board::move[_x - 2][_y + 2] = 1;
            }
            if (_x + 2 <= 8 && _y + 2 <= 9 && Board::board[_x + 1][_y + 1] == 0 && Board::board[_x + 2][_y + 2] != 1)
            {
                Board::move[_x + 2][_y + 2] = 1;
            }
        }
        else if (color == -1)
        {
            // Check if the move is valid
            if (_x - 2 >= 0 && _y - 2 >= 0 && Board::board[_x - 1][_y - 1] == 0 && Board::board[_x - 2][_y - 2] != -1)
            {
                Board::move[_x - 2][_y - 2] = 1;
            }
            if (_x + 2 <= 8 && _y - 2 >= 0 && Board::board[_x + 1][_y - 1] == 0 && Board::board[_x + 2][_y - 2] != -1)
            {
                Board::move[_x + 2][_y - 2] = 1;
            }
            if (_x - 2 >= 0 && _y + 2 <= 4 && Board::board[_x - 1][_y + 1] == 0 && Board::board[_x - 2][_y + 2] != -1)
            {
                Board::move[_x - 2][_y + 2] = 1;
            }
            if (_x + 2 <= 8 && _y + 2 <= 4 && Board::board[_x + 1][_y + 1] == 0 && Board::board[_x + 2][_y + 2] != -1)
            {
                Board::move[_x + 2][_y + 2] = 1;
            }
        }
    }
    else // for virtual moves
    {
        if (color == 1)
        {
            // Check if the move is valid
            if (fakeX - 2 >= 0 && fakeY - 2 >= 5 && Board::board[fakeX - 1][fakeY - 1] == 0 && Board::board[fakeX - 2][fakeY - 2] != 1)
            {
                Board::virtualMove[fakeX - 2][fakeY - 2] = 1;
            }
            if (fakeX + 2 <= 8 && fakeY - 2 >= 5 && Board::board[fakeX + 1][fakeY - 1] == 0 && Board::board[fakeX + 2][fakeY - 2] != 1)
            {
                Board::virtualMove[fakeX + 2][fakeY - 2] = 1;
            }
            if (fakeX - 2 >= 0 && fakeY + 2 <= 9 && Board::board[fakeX - 1][fakeY + 1] == 0 && Board::board[fakeX - 2][fakeY + 2] != 1)
            {
                Board::virtualMove[fakeX - 2][fakeY + 2] = 1;
            }
            if (fakeX + 2 <= 8 && fakeY + 2 <= 9 && Board::board[fakeX + 1][fakeY + 1] == 0 && Board::board[fakeX + 2][fakeY + 2] != 1)
            {
                Board::virtualMove[fakeX + 2][fakeY + 2] = 1;
            }
        }
        else if (color == -1)
        {
            // Check if the move is valid
            if (fakeX - 2 >= 0 && fakeY - 2 >= 0 && Board::board[fakeX - 1][fakeY - 1] == 0 && Board::board[fakeX - 2][fakeY - 2] != -1)
            {
                Board::virtualMove[fakeX - 2][fakeY - 2] = 1;
            }
            if (fakeX + 2 <= 8 && fakeY - 2 >= 0 && Board::board[fakeX + 1][fakeY - 1] == 0 && Board::board[fakeX + 2][fakeY - 2] != -1)
            {
                Board::virtualMove[fakeX + 2][fakeY - 2] = 1;
            }
            if (fakeX - 2 >= 0 && fakeY + 2 <= 4 && Board::board[fakeX - 1][fakeY + 1] == 0 && Board::board[fakeX - 2][fakeY + 2] != -1)
            {
                Board::virtualMove[fakeX - 2][fakeY + 2] = 1;
            }
            if (fakeX + 2 <= 8 && fakeY + 2 <= 4 && Board::board[fakeX + 1][fakeY + 1] == 0 && Board::board[fakeX + 2][fakeY + 2] != -1)
            {
                Board::virtualMove[fakeX + 2][fakeY + 2] = 1;
            }
        }
    }
}

// Parameterized constructor for the Horse class
Horse::Horse(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    name = "Horse";
    fakeX = x;
    fakeY = y;
}

// Function to determine the possible moves for the Horse piece
void Horse::canMove(int show)
{
    if (show == 0) // for actual moves
    {
        if (color == 1)
        {
            // Check if the move is valid
            if (_x - 2 >= 0 && _y - 1 >= 0 && Board::board[_x - 1][_y] == 0 && Board::board[_x - 2][_y - 1] != 1)
            {
                Board::move[_x - 2][_y - 1] = 1;
            }
            if (_x + 2 <= 8 && _y - 1 >= 0 && Board::board[_x + 1][_y] == 0 && Board::board[_x + 2][_y - 1] != 1)
            {
                Board::move[_x + 2][_y - 1] = 1;
            }
            if (_x - 2 >= 0 && _y + 1 <= 9 && Board::board[_x - 1][_y] == 0 && Board::board[_x - 2][_y + 1] != 1)
            {
                Board::move[_x - 2][_y + 1] = 1;
            }
            if (_x + 2 <= 8 && _y + 1 <= 9 && Board::board[_x + 1][_y] == 0 && Board::board[_x + 2][_y + 1] != 1)
            {
                Board::move[_x + 2][_y + 1] = 1;
            }
            if (_x + 1 <= 8 && _y - 2 >= 0 && Board::board[_x][_y - 1] == 0 && Board::board[_x + 1][_y - 2] != 1)
            {
                Board::move[_x + 1][_y - 2] = 1;
            }
            if (_x + 1 <= 8 && _y + 2 <= 9 && Board::board[_x][_y + 1] == 0 && Board::board[_x + 1][_y + 2] != 1)
            {
                Board::move[_x + 1][_y + 2] = 1;
            }
            if (_x - 1 >= 0 && _y - 2 >= 0 && Board::board[_x][_y - 1] == 0 && Board::board[_x - 1][_y - 2] != 1)
            {
                Board::move[_x - 1][_y - 2] = 1;
            }
            if (_x - 1 >= 0 && _y + 2 <= 9 && Board::board[_x][_y + 1] == 0 && Board::board[_x - 1][_y + 2] != 1)
            {
                Board::move[_x - 1][_y + 2] = 1;
            }
        }
        else if (color == -1)
        {
            // Check if the move is valid
            if (_x - 2 >= 0 && _y - 1 >= 0 && Board::board[_x - 1][_y] == 0 && Board::board[_x - 2][_y - 1] != -1)
            {
                Board::move[_x - 2][_y - 1] = 1;
            }
            if (_x + 2 <= 8 && _y - 1 >= 0 && Board::board[_x + 1][_y] == 0 && Board::board[_x + 2][_y - 1] != -1)
            {
                Board::move[_x + 2][_y - 1] = 1;
            }
            if (_x - 2 >= 0 && _y + 1 <= 9 && Board::board[_x - 1][_y] == 0 && Board::board[_x - 2][_y + 1] != -1)
            {
                Board::move[_x - 2][_y + 1] = 1;
            }
            if (_x + 2 <= 8 && _y + 1 <= 9 && Board::board[_x + 1][_y] == 0 && Board::board[_x + 2][_y + 1] != -1)
            {
                Board::move[_x + 2][_y + 1] = 1;
            }
            if (_x + 1 <= 8 && _y - 2 >= 0 && Board::board[_x][_y - 1] == 0 && Board::board[_x + 1][_y - 2] != -1)
            {
                Board::move[_x + 1][_y - 2] = 1;
            }
            if (_x + 1 <= 8 && _y + 2 <= 9 && Board::board[_x][_y + 1] == 0 && Board::board[_x + 1][_y + 2] != -1)
            {
                Board::move[_x + 1][_y + 2] = 1;
            }
            if (_x - 1 >= 0 && _y - 2 >= 0 && Board::board[_x][_y - 1] == 0 && Board::board[_x - 1][_y - 2] != -1)
            {
                Board::move[_x - 1][_y - 2] = 1;
            }
            if (_x - 1 >= 0 && _y + 2 <= 9 && Board::board[_x][_y + 1] == 0 && Board::board[_x - 1][_y + 2] != -1)
            {
                Board::move[_x - 1][_y + 2] = 1;
            }
        }
    }
    else // for virtual moves
    {
        if (color == 1)
        {
            // Check if the move is valid
            if (fakeX - 2 >= 0 && fakeY - 1 >= 0 && Board::board[fakeX - 1][fakeY] == 0 && Board::board[fakeX - 2][fakeY - 1] != 1)
            {
                Board::virtualMove[fakeX - 2][fakeY - 1] = 1;
            }
            if (fakeX + 2 <= 8 && fakeY - 1 >= 0 && Board::board[fakeX + 1][fakeY] == 0 && Board::board[fakeX + 2][fakeY - 1] != 1)
            {
                Board::virtualMove[fakeX + 2][fakeY - 1] = 1;
            }
            if (fakeX - 2 >= 0 && fakeY + 1 <= 9 && Board::board[fakeX - 1][fakeY] == 0 && Board::board[fakeX - 2][fakeY + 1] != 1)
            {
                Board::virtualMove[fakeX - 2][fakeY + 1] = 1;
            }
            if (fakeX + 2 <= 8 && fakeY + 1 <= 9 && Board::board[fakeX + 1][fakeY] == 0 && Board::board[fakeX + 2][fakeY + 1] != 1)
            {
                Board::virtualMove[fakeX + 2][fakeY + 1] = 1;
            }
            if (fakeX + 1 <= 8 && fakeY - 2 >= 0 && Board::board[fakeX][fakeY - 1] == 0 && Board::board[fakeX + 1][fakeY - 2] != 1)
            {
                Board::virtualMove[fakeX + 1][fakeY - 2] = 1;
            }
            if (fakeX + 1 <= 8 && fakeY + 2 <= 9 && Board::board[fakeX][fakeY + 1] == 0 && Board::board[fakeX + 1][fakeY + 2] != 1)
            {
                Board::virtualMove[fakeX + 1][fakeY + 2] = 1;
            }
            if (fakeX - 1 >= 0 && fakeY - 2 >= 0 && Board::board[fakeX][fakeY - 1] == 0 && Board::board[fakeX - 1][fakeY - 2] != 1)
            {
                Board::virtualMove[fakeX - 1][fakeY - 2] = 1;
            }
            if (fakeX - 1 >= 0 && fakeY + 2 <= 9 && Board::board[fakeX][fakeY + 1] == 0 && Board::board[fakeX - 1][fakeY + 2] != 1)
            {
                Board::virtualMove[fakeX - 1][fakeY + 2] = 1;
            }
        }
        else if (color == -1)
        {
            // Check if the move is valid
            if (fakeX - 2 >= 0 && fakeY - 1 >= 0 && Board::board[fakeX - 1][fakeY] == 0 && Board::board[fakeX - 2][fakeY - 1] != -1)
            {
                Board::virtualMove[fakeX - 2][fakeY - 1] = 1;
            }
            if (fakeX + 2 <= 8 && fakeY - 1 >= 0 && Board::board[fakeX + 1][fakeY] == 0 && Board::board[fakeX + 2][fakeY - 1] != -1)
            {
                Board::virtualMove[fakeX + 2][fakeY - 1] = 1;
            }
            if (fakeX - 2 >= 0 && fakeY + 1 <= 9 && Board::board[fakeX - 1][fakeY] == 0 && Board::board[fakeX - 2][fakeY + 1] != -1)
            {
                Board::virtualMove[fakeX - 2][fakeY + 1] = 1;
            }
            if (fakeX + 2 <= 8 && fakeY + 1 <= 9 && Board::board[fakeX + 1][fakeY] == 0 && Board::board[fakeX + 2][fakeY + 1] != -1)
            {
                Board::virtualMove[fakeX + 2][fakeY + 1] = 1;
            }
            if (fakeX + 1 <= 8 && fakeY - 2 >= 0 && Board::board[fakeX][fakeY - 1] == 0 && Board::board[fakeX + 1][fakeY - 2] != -1)
            {
                Board::virtualMove[fakeX + 1][fakeY - 2] = 1;
            }
            if (fakeX + 1 <= 8 && fakeY + 2 <= 9 && Board::board[fakeX][fakeY + 1] == 0 && Board::board[fakeX + 1][fakeY + 2] != -1)
            {
                Board::virtualMove[fakeX + 1][fakeY + 2] = 1;
            }
            if (fakeX - 1 >= 0 && fakeY - 2 >= 0 && Board::board[fakeX][fakeY - 1] == 0 && Board::board[fakeX - 1][fakeY - 2] != -1)
            {
                Board::virtualMove[fakeX - 1][fakeY - 2] = 1;
            }
            if (fakeX - 1 >= 0 && fakeY + 2 <= 9 && Board::board[fakeX][fakeY + 1] == 0 && Board::board[fakeX - 1][fakeY + 2] != -1)
            {
                Board::virtualMove[fakeX - 1][fakeY + 2] = 1;
            }
        }
    }
}

// Parameterized constructor for the Soldier class
Soldier::Soldier(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    name = "Soldier";
    fakeX = x;
    fakeY = y;
}

// Function to determine the possible moves for the Soldier piece
void Soldier::canMove(int show)
{
    if (show == 0) // for actual moves
    {
        if (color == 1)
        {
            if (_y >= 5) // before crossing the river
            {
                // Check if the move is valid
                if (_y - 1 >= 0 && Board::board[_x][_y - 1] != 1)
                {
                    Board::move[_x][_y - 1] = 1;
                }
            }
            else
            {
                // Check if the move is valid
                if (_y - 1 >= 0 && Board::board[_x][_y - 1] != 1)
                {
                    Board::move[_x][_y - 1] = 1;
                }
                if (_x + 1 <= 8 && Board::board[_x + 1][_y] != 1)
                {
                    Board::move[_x + 1][_y] = 1;
                }
                if (_x - 1 >= 0 && Board::board[_x - 1][_y] != 1)
                {
                    Board::move[_x - 1][_y] = 1;
                }
            }
        }
        else if (color == -1)
        {
            if (_y <= 4) // before crossing the river
            {
                // Check if the move is valid
                if (_y + 1 >= 0 && Board::board[_x][_y + 1] != -1)
                {
                    Board::move[_x][_y + 1] = 1;
                }
            }
            else
            {
                // Check if the move is valid
                if (_y + 1 >= 0 && Board::board[_x][_y + 1] != -1)
                {
                    Board::move[_x][_y + 1] = 1;
                }
                if (_x + 1 <= 8 && Board::board[_x + 1][_y] != -1)
                {
                    Board::move[_x + 1][_y] = 1;
                }
                if (_x - 1 >= 0 && Board::board[_x - 1][_y] != -1)
                {
                    Board::move[_x - 1][_y] = 1;
                }
            }
        }
    }
    else // for virtual moves
    {
        if (color == 1)
        {
            if (fakeY >= 5) // before crossing the river
            {
                // Check if the move is valid
                if (fakeY - 1 >= 0 && Board::board[fakeX][fakeY - 1] != 1)
                {
                    Board::virtualMove[fakeX][fakeY - 1] = 1;
                }
            }
            else
            {
                // Check if the move is valid
                if (fakeY - 1 >= 0 && Board::board[fakeX][fakeY - 1] != 1)
                {
                    Board::virtualMove[fakeX][fakeY - 1] = 1;
                }
                if (fakeX + 1 <= 8 && Board::board[fakeX + 1][fakeY] != 1)
                {
                    Board::virtualMove[fakeX + 1][fakeY] = 1;
                }
                if (fakeX - 1 >= 0 && Board::board[fakeX - 1][fakeY] != 1)
                {
                    Board::virtualMove[fakeX - 1][fakeY] = 1;
                }
            }
        }
        else if (color == -1)
        {
            if (fakeY <= 4) // before crossing the river
            {
                // Check if the move is valid
                if (fakeY + 1 >= 0 && Board::board[fakeX][fakeY + 1] != -1)
                {
                    Board::virtualMove[fakeX][fakeY + 1] = 1;
                }
            }
            else
            {
                // Check if the move is valid
                if (fakeY + 1 >= 0 && Board::board[fakeX][fakeY + 1] != -1)
                {
                    Board::virtualMove[fakeX][fakeY + 1] = 1;
                }
                if (fakeX + 1 <= 8 && Board::board[fakeX + 1][fakeY] != -1)
                {
                    Board::virtualMove[fakeX + 1][fakeY] = 1;
                }
                if (fakeX - 1 >= 0 && Board::board[fakeX - 1][fakeY] != -1)
                {
                    Board::virtualMove[fakeX - 1][fakeY] = 1;
                }
            }
        }
    }
}

// Parameterized constructor for the Chariot class
Chariot::Chariot(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    name = "Chariot";
    fakeX = x;
    fakeY = y;
}

// Function to determine the possible moves for the Chariot piece
void Chariot::canMove(int show)
{
    if (show == 0) // for actual moves
    {
        if (color == 1)
        {
            // Check if the move is valid
            for (int x = 1; x <= 8; x++)
            {
                if (_x + x <= 8 && Board::board[_x + x][_y] == 0)
                {
                    Board::move[_x + x][_y] = 1;
                }
                else if (_x + x <= 8 && Board::board[_x + x][_y] == -1)
                {
                    Board::move[_x + x][_y] = 1;
                    break;
                }
                else break;
            }
            for (int x = 1; x <= 8; x++)
            {
                if (_x - x >= 0 && Board::board[_x - x][_y] == 0)
                {
                    Board::move[_x - x][_y] = 1;
                }
                else if (_x - x >= 0 && Board::board[_x - x][_y] == -1)
                {
                    Board::move[_x - x][_y] = 1;
                    break;
                }
                else break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (_y + x <= 9 && Board::board[_x][_y + x] == 0)
                {
                    Board::move[_x][_y + x] = 1;
                }
                else if (_y + x <= 9 && Board::board[_x][_y + x] == -1)
                {
                    Board::move[_x][_y + x] = 1;
                    break;
                }
                else break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (_y - x >= 0 && Board::board[_x][_y - x] == 0)
                {
                    Board::move[_x][_y - x] = 1;
                }
                else if (_y - x >= 0 && Board::board[_x][_y - x] == -1)
                {
                    Board::move[_x][_y - x] = 1;
                    break;
                }
                else break;
            }
        }
        else if (color == -1)
        {
            // Check if the move is valid
            for (int x = 1; x <= 8; x++)
            {
                if (_x + x <= 8 && Board::board[_x + x][_y] == 0)
                {
                    Board::move[_x + x][_y] = 1;
                }
                else if (_x + x <= 8 && Board::board[_x + x][_y] == 1)
                {
                    Board::move[_x + x][_y] = 1;
                    break;
                }
                else break;
            }
            for (int x = 1; x <= 8; x++)
            {
                if (_x - x >= 0 && Board::board[_x - x][_y] == 0)
                {
                    Board::move[_x - x][_y] = 1;
                }
                else if (_x - x >= 0 && Board::board[_x - x][_y] == 1)
                {
                    Board::move[_x - x][_y] = 1;
                    break;
                }
                else break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (_y + x <= 9 && Board::board[_x][_y + x] == 0)
                {
                    Board::move[_x][_y + x] = 1;
                }
                else if (_y + x <= 9 && Board::board[_x][_y + x] == 1)
                {
                    Board::move[_x][_y + x] = 1;
                    break;
                }
                else break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (_y - x >= 0 && Board::board[_x][_y - x] == 0)
                {
                    Board::move[_x][_y - x] = 1;
                }
                else if (_y - x >= 0 && Board::board[_x][_y - x] == 1)
                {
                    Board::move[_x][_y - x] = 1;
                    break;
                }
                else break;
            }
        }
    }
    else // for virtual moves
    {
        if (color == 1)
        {
            // Check if the move is valid
            for (int x = 1; x <= 8; x++)
            {
                if (fakeX + x <= 8 && Board::board[fakeX + x][fakeY] == 0)
                {
                    Board::virtualMove[fakeX + x][fakeY] = 1;
                }
                else if (fakeX + x <= 8 && Board::board[fakeX + x][fakeY] == -1)
                {
                    Board::virtualMove[fakeX + x][fakeY] = 1;
                    break;
                }
                else break;
            }
            for (int x = 1; x <= 8; x++)
            {
                if (fakeX - x >= 0 && Board::board[fakeX - x][fakeY] == 0)
                {
                    Board::virtualMove[fakeX - x][fakeY] = 1;
                }
                else if (fakeX - x >= 0 && Board::board[fakeX - x][fakeY] == -1)
                {
                    Board::virtualMove[fakeX - x][fakeY] = 1;
                    break;
                }
                else break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (fakeY + x <= 9 && Board::board[fakeX][fakeY + x] == 0)
                {
                    Board::virtualMove[fakeX][fakeY + x] = 1;
                }
                else if (fakeY + x <= 9 && Board::board[fakeX][fakeY + x] == -1)
                {
                    Board::virtualMove[fakeX][fakeY + x] = 1;
                    break;
                }
                else break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (fakeY - x >= 0 && Board::board[fakeX][fakeY - x] == 0)
                {
                    Board::virtualMove[fakeX][fakeY - x] = 1;
                }
                else if (fakeY - x >= 0 && Board::board[fakeX][fakeY - x] == -1)
                {
                    Board::virtualMove[fakeX][fakeY - x] = 1;
                    break;
                }
                else break;
            }
        }
        else if (color == -1)
        {
            // Check if the move is valid
            for (int x = 1; x <= 8; x++)
            {
                if (fakeX + x <= 8 && Board::board[fakeX + x][fakeY] == 0)
                {
                    Board::virtualMove[fakeX + x][fakeY] = 1;
                }
                else if (fakeX + x <= 8 && Board::board[fakeX + x][fakeY] == 1)
                {
                    Board::virtualMove[fakeX + x][fakeY] = 1;
                    break;
                }
                else break;
            }
            for (int x = 1; x <= 8; x++)
            {
                if (fakeX - x >= 0 && Board::board[fakeX - x][fakeY] == 0)
                {
                    Board::virtualMove[fakeX - x][fakeY] = 1;
                }
                else if (fakeX - x >= 0 && Board::board[fakeX - x][fakeY] == 1)
                {
                    Board::virtualMove[fakeX - x][fakeY] = 1;
                    break;
                }
                else break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (fakeY + x <= 9 && Board::board[fakeX][fakeY + x] == 0)
                {
                    Board::virtualMove[fakeX][fakeY + x] = 1;
                }
                else if (fakeY + x <= 9 && Board::board[fakeX][fakeY + x] == 1)
                {
                    Board::virtualMove[fakeX][fakeY + x] = 1;
                    break;
                }
                else break;
            }
            for (int x = 1; x <= 9; x++)
            {
                if (fakeY - x >= 0 && Board::board[fakeX][fakeY - x] == 0)
                {
                    Board::virtualMove[fakeX][fakeY - x] = 1;
                }
                else if (fakeY - x >= 0 && Board::board[fakeX][fakeY - x] == 1)
                {
                    Board::virtualMove[fakeX][fakeY - x] = 1;
                    break;
                }
                else break;
            }
        }
    }
}

// Parameterized constructor for the Cannon class
Cannon::Cannon(int x, int y, int col, string src)
{
    _x = x;
    _y = y;
    firstX = x;
    firstY = y;
    pic = src;
    color = col;
    name = "Cannon";
    fakeX = x;
    fakeY = y;
}

// Function to determine the possible moves for the Cannon piece
void Cannon::canMove(int show)
{
    if (show == 0) // for actual moves
    {
        if (color == 1)
        {
            skip = false; // Check if there is a block (skip)
            for (int x = 1; x <= 8; x++)
            {
                if (_x + x <= 8 && Board::board[_x + x][_y] == 0 && !skip)
                {
                    Board::move[_x + x][_y] = 1;
                }
                else if (_x + x <= 8 && Board::board[_x + x][_y] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (_x + x <= 8 && Board::board[_x + x][_y] == 1 && skip)
                {
                    break;
                }
                else if (_x + x <= 8 && Board::board[_x + x][_y] == -1 && skip)
                {
                    Board::move[_x + x][_y] = 1; // Can capture the piece
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 8; x++)
            {
                if (_x - x >= 0 && Board::board[_x - x][_y] == 0 && !skip)
                {
                    Board::move[_x - x][_y] = 1;
                }
                else if (_x - x >= 0 && Board::board[_x - x][_y] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (_x - x >= 0 && Board::board[_x - x][_y] == 1 && skip)
                {
                    break;
                }
                else if (_x - x >= 0 && Board::board[_x - x][_y] == -1 && skip)
                {
                    Board::move[_x - x][_y] = 1; // Can capture the piece
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (_y + x <= 9 && Board::board[_x][_y + x] == 0 && !skip)
                {
                    Board::move[_x][_y + x] = 1;
                }
                else if (_y + x <= 9 && Board::board[_x][_y + x] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (_y + x <= 9 && Board::board[_x][_y + x] == 1 && skip)
                {
                    break;
                }
                else if (_y + x <= 9 && Board::board[_x][_y + x] == -1 && skip)
                {
                    Board::move[_x][_y + x] = 1; // Can capture the piece
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (_y - x >= 0 && Board::board[_x][_y - x] == 0 && !skip)
                {
                    Board::move[_x][_y - x] = 1;
                }
                else if (_y - x >= 0 && Board::board[_x][_y - x] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (_y - x >= 0 && Board::board[_x][_y - x] == 1 && skip)
                {
                    break;
                }
                else if (_y - x >= 0 && Board::board[_x][_y - x] == -1 && skip)
                {
                    Board::move[_x][_y - x] = 1; // Can capture the piece
                    break;
                }
            }
        }
        else if (color == -1)
        {
            skip = false; // Check if there is a block (skip)
            for (int x = 1; x <= 8; x++)
            {
                if (_x + x <= 8 && Board::board[_x + x][_y] == 0 && !skip)
                {
                    Board::move[_x + x][_y] = 1;
                }
                else if (_x + x <= 8 && Board::board[_x + x][_y] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (_x + x <= 8 && Board::board[_x + x][_y] == -1 && skip)
                {
                    break;
                }
                else if (_x + x <= 8 && Board::board[_x + x][_y] == 1 && skip)
                {
                    Board::move[_x + x][_y] = 1; // Can capture the piece
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 8; x++)
            {
                if (_x - x >= 0 && Board::board[_x - x][_y] == 0 && !skip)
                {
                    Board::move[_x - x][_y] = 1;
                }
                else if (_x - x >= 0 && Board::board[_x - x][_y] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (_x - x >= 0 && Board::board[_x - x][_y] == -1 && skip)
                {
                    break;
                }
                else if (_x - x >= 0 && Board::board[_x - x][_y] == 1 && skip)
                {
                    Board::move[_x - x][_y] = 1; // Can capture the piece
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (_y + x <= 9 && Board::board[_x][_y + x] == 0 && !skip)
                {
                    Board::move[_x][_y + x] = 1;
                }
                else if (_y + x <= 9 && Board::board[_x][_y + x] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (_y + x <= 9 && Board::board[_x][_y + x] == -1 && skip)
                {
                    break;
                }
                else if (_y + x <= 9 && Board::board[_x][_y + x] == 1 && skip)
                {
                    Board::move[_x][_y + x] = 1; // Can capture the piece
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (_y - x >= 0 && Board::board[_x][_y - x] == 0 && !skip)
                {
                    Board::move[_x][_y - x] = 1;
                }
                else if (_y - x >= 0 && Board::board[_x][_y - x] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (_y - x >= 0 && Board::board[_x][_y - x] == -1 && skip)
                {
                    break;
                }
                else if (_y - x >= 0 && Board::board[_x][_y - x] == 1 && skip)
                {
                    Board::move[_x][_y - x] = 1; // Can capture the piece
                    break;
                }
            }
        }
    }
    else // for virtual moves
    {
        if (color == 1)
        {
            skip = false; // Check if there is a block (skip)
            for (int x = 1; x <= 8; x++)
            {
                if (fakeX + x <= 8 && Board::board[fakeX + x][fakeY] == 0 && !skip)
                {
                    Board::virtualMove[fakeX + x][fakeY] = 1;
                }
                else if (fakeX + x <= 8 && Board::board[fakeX + x][fakeY] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (fakeX + x <= 8 && Board::board[fakeX + x][fakeY] == 1 && skip)
                {
                    break;
                }
                else if (fakeX + x <= 8 && Board::board[fakeX + x][fakeY] == -1 && skip)
                {
                    Board::virtualMove[fakeX + x][fakeY] = 1; // Can capture the piece
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 8; x++)
            {
                if (fakeX - x >= 0 && Board::board[fakeX - x][fakeY] == 0 && !skip)
                {
                    Board::virtualMove[fakeX - x][fakeY] = 1;
                }
                else if (fakeX - x >= 0 && Board::board[fakeX - x][fakeY] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (fakeX - x >= 0 && Board::board[fakeX - x][fakeY] == 1 && skip)
                {
                    break;
                }
                else if (fakeX - x >= 0 && Board::board[fakeX - x][fakeY] == -1 && skip)
                {
                    Board::virtualMove[fakeX - x][fakeY] = 1; // Can capture the piece
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (fakeY + x <= 9 && Board::board[fakeX][fakeY + x] == 0 && !skip)
                {
                    Board::virtualMove[fakeX][fakeY + x] = 1;
                }
                else if (fakeY + x <= 9 && Board::board[fakeX][fakeY + x] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (fakeY + x <= 9 && Board::board[fakeX][fakeY + x] == 1 && skip)
                {
                    break;
                }
                else if (fakeY + x <= 9 && Board::board[fakeX][fakeY + x] == -1 && skip)
                {
                    Board::virtualMove[fakeX][fakeY + x] = 1; // Can capture the piece
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (fakeY - x >= 0 && Board::board[fakeX][fakeY - x] == 0 && !skip)
                {
                    Board::virtualMove[fakeX][fakeY - x] = 1;
                }
                else if (fakeY - x >= 0 && Board::board[fakeX][fakeY - x] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (fakeY - x >= 0 && Board::board[fakeX][fakeY - x] == 1 && skip)
                {
                    break;
                }
                else if (fakeY - x >= 0 && Board::board[fakeX][fakeY - x] == -1 && skip)
                {
                    Board::virtualMove[fakeX][fakeY - x] = 1; // Can capture the piece
                    break;
                }
            }
        }
        else if (color == -1)
        {
            skip = false; // Check if there is a block (skip)
            for (int x = 1; x <= 8; x++)
            {
                if (fakeX + x <= 8 && Board::board[fakeX + x][fakeY] == 0 && !skip)
                {
                    Board::virtualMove[fakeX + x][fakeY] = 1;
                }
                else if (fakeX + x <= 8 && Board::board[fakeX + x][fakeY] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (fakeX + x <= 8 && Board::board[fakeX + x][fakeY] == -1 && skip)
                {
                    break;
                }
                else if (fakeX + x <= 8 && Board::board[fakeX + x][fakeY] == 1 && skip)
                {
                    Board::virtualMove[fakeX + x][fakeY] = 1; // Can capture the piece
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 8; x++)
            {
                if (fakeX - x >= 0 && Board::board[fakeX - x][fakeY] == 0 && !skip)
                {
                    Board::virtualMove[fakeX - x][fakeY] = 1;
                }
                else if (fakeX - x >= 0 && Board::board[fakeX - x][fakeY] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (fakeX - x >= 0 && Board::board[fakeX - x][fakeY] == -1 && skip)
                {
                    break;
                }
                else if (fakeX - x >= 0 && Board::board[fakeX - x][fakeY] == 1 && skip)
                {
                    Board::virtualMove[fakeX - x][fakeY] = 1; // Can capture the piece
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (fakeY + x <= 9 && Board::board[fakeX][fakeY + x] == 0 && !skip)
                {
                    Board::virtualMove[fakeX][fakeY + x] = 1;
                }
                else if (fakeY + x <= 9 && Board::board[fakeX][fakeY + x] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (fakeY + x <= 9 && Board::board[fakeX][fakeY + x] == -1 && skip)
                {
                    break;
                }
                else if (fakeY + x <= 9 && Board::board[fakeX][fakeY + x] == 1 && skip)
                {
                    Board::virtualMove[fakeX][fakeY + x] = 1; // Can capture the piece
                    break;
                }
            }
            skip = false;
            for (int x = 1; x <= 9; x++)
            {
                if (fakeY - x >= 0 && Board::board[fakeX][fakeY - x] == 0 && !skip)
                {
                    Board::virtualMove[fakeX][fakeY - x] = 1;
                }
                else if (fakeY - x >= 0 && Board::board[fakeX][fakeY - x] != 0 && !skip)
                {
                    skip = true; // Found a block
                }
                else if (fakeY - x >= 0 && Board::board[fakeX][fakeY - x] == -1 && skip)
                {
                    break;
                }
                else if (fakeY - x >= 0 && Board::board[fakeX][fakeY - x] == 1 && skip)
                {
                    Board::virtualMove[fakeX][fakeY - x] = 1; // Can capture the piece
                    break;
                }
            }
        }
    }
}
