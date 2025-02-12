#include "GameManager.h"
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstdlib>

// Initialize the current player to 0
int GameManager::currentPlayer = 0;

// Constructor for the GameManager class
GameManager::GameManager()
{
    srand(time(NULL));
    Board::onBoard = onBoard;
    fstream file;
    file.open("log.txt", ios::out | ios::trunc);
    file.close();
}

// Function to show the menu
void GameManager::showMenu(){
    v.menu();
    v.show();
}

// Function to restart the game
void GameManager::restartGame()
{
    Board::clearVirtualMove();
    Board::clearMove();
    Board::resetBoard();
    for (int i = 0; i < Board::onBoard.size(); i++)  {
        Board::onBoard[i]->resetChess();
    }
    GameManager::currentPlayer = 0;
    fstream file;
    file.open("log.txt", ios::out | ios::trunc);
    file.close();
}

// Function to load a game from a file
void GameManager::loadFile(string path)
{
    GameManager::restartGame();
    fstream file;
    file.open(path, ios::in);
    string input;
    int nowX, nowY, nextX, nextY;
    while (getline(file, input)) {
        for (int i = 0; i < input.length(); i++) {
            if (!isdigit(input[i])) input[i] = ' ';
        }
        cout << input << endl;
        stringstream in(input);
        in >> nowX >> nowX >> nowY >> nextX >> nextY;

        for (int i = 0; i < Board::onBoard.size(); i++) {
            if (Board::onBoard[i]->getX() == nowX && Board::onBoard[i]->getY() == nowY && Board::onBoard[i]->alive) {
                Board::onBoard[i]->canMove(0);
                cout << "find!\n";

                if (Board::board[nextX][nextY] != 0) {
                    for (int j = 0; j < Board::onBoard.size(); j++) {
                        if (Board::onBoard[j]->getX() == nextX && Board::onBoard[j]->getY() == nextY && Board::onBoard[j]->alive) {
                            Board::onBoard[j]->alive = false;
                            Board::onBoard[j]->fakeAlive = false;
                            break;
                        }
                    }
                }
                
                Board::onBoard[i]->move(nextX, nextY);
                Board::onBoard[i]->makeLog(nowX, nowY);
                Board::clearMove();
                break;
            }
        }
    }
    Board::clearMove();
    file.close();
}

// Function to write a log entry to the log file
void GameManager::writeLog(string log)
{
    fstream file;
    file.open("log.txt", ios::out | ios::app);
    file << log;
    file.close();
}

// Function to add a chess piece to the game
void GameManager::pushIn(Chess* ch)
{
    onBoard.push_back(ch);
    Board::board[ch->getX()][ch->getY()] = ch->color;
    Board::onBoard = onBoard;
}

// Function to check if both kings are still alive
bool GameManager::checkKing()
{
    if (Board::RKing->alive && Board::BKing->alive) {
        return true;
    }
    else {
        return false;
    }
}

// Function to check if a king is in check
bool GameManager::isCheck(int flag) // flag 1: actual check, 0: simulated check
{
    if (flag == 1) {
        for (int i = 0; i < Board::onBoard.size(); i++)
        {
            if (currentPlayer % 2 == 0) // red's turn
            {
                if (Board::onBoard[i]->color == -1 && Board::onBoard[i]->alive) // black chess
                {
                    Board::onBoard[i]->canMove(1);
                    int x = Board::RKing->getX();
                    int y = Board::RKing->getY();

                    if (Board::virtualMove[x][y] == 1)
                    {
                        return true;
                    }
                }
            }
            else  // black's turn
            {
                if (Board::onBoard[i]->color == 1 && Board::onBoard[i]->alive) // red chess
                {
                    Board::onBoard[i]->canMove(1);
                    int x = Board::BKing->getX();
                    int y = Board::BKing->getY();

                    if (Board::virtualMove[x][y] == 1)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    else if (flag == 0) {
        for (int i = 0; i < Board::onBoard.size(); i++)
        {
            if (currentPlayer % 2 == 0) // red's turn
            {
                if (Board::onBoard[i]->color == -1 && Board::onBoard[i]->fakeAlive) // black chess
                {
                    Board::onBoard[i]->canMove(1);
                    int x = Board::RKing->getFakeX();
                    int y = Board::RKing->getFakeY();

                    if (Board::virtualMove[x][y] == 1)
                    {
                        return true;
                    }
                }
            }
            else  // black's turn
            {
                if (Board::onBoard[i]->color == 1 && Board::onBoard[i]->fakeAlive) // red chess
                {
                    Board::onBoard[i]->canMove(1);
                    int x = Board::BKing->getFakeX();
                    int y = Board::BKing->getFakeY();

                    if (Board::virtualMove[x][y] == 1)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}

// Structure to represent a position on the board
typedef struct Position {
    int x;
    int y;
};

// Function to simulate an AI move
void GameManager::aiGame()
{
    int randNum = rand() % Board::onBoard.size() / 2 + 1;
    int count = 0;
    for (int i = 0; i < Board::onBoard.size(); i++) {
        if (Board::onBoard[i]->color == -1) { // black piece
            count++;
        }
        if (count == randNum && Board::onBoard[i]->alive) {
            int beforeX = Board::onBoard[i]->getX();
            int beforeY = Board::onBoard[i]->getY();

            Board::onBoard[i]->canMove(0);
            vector<Position> list;
            list.clear();
            for (int j = 0; j < 9; j++) {
                for (int k = 0; k < 10; k++) {
                    if (Board::move[j][k] == 1) {
                        list.push_back({ j,k });
                    }
                }
            }
            if (list.size() == 0) {
                randNum++;
            }
            else {
                randNum = rand() % list.size();
                if (Board::board[list[randNum].x][list[randNum].y] != 0) {
                    for (int j = 0; j < Board::onBoard.size(); j++) {
                        if (Board::onBoard[j]->getX() == list[randNum].x && Board::onBoard[j]->getY() == list[randNum].y 
                            && Board::onBoard[j]->alive) {
                            Board::onBoard[j]->alive = false;
                            Board::onBoard[j]->fakeAlive = false;
                            break;
                        }
                    }
                }
                Board::onBoard[i]->move(list[randNum].x, list[randNum].y);
                Board::onBoard[i]->makeLog(beforeX, beforeY);
                Board::clearMove();
                break;
            }
        }
        else if(count == randNum && !Board::onBoard[i]->alive) {
            randNum++;
        }
    }
}

// Function to check for stalemate
bool GameManager::stalemate()
{
    Board::clearVirtualMove();
    int nowTurn = currentPlayer % 2;
    if (nowTurn == 0) nowTurn = 1;
    else nowTurn = -1;
    for (int i = 0; i < Board::onBoard.size(); i++) {
        Board::clearMove();
        if (Board::onBoard[i]->color == nowTurn && Board::onBoard[i]->alive) {
            Board::onBoard[i]->canMove(0);
            vector<Position> list;
            list.clear();
            for (int j = 0; j < 9; j++) {
                for (int k = 0; k < 10; k++) {
                    if (Board::move[j][k] == 1)  list.push_back({ j,k });
                }
            }
            for (int k = 0; k < list.size(); k++) {
                int col = Board::board[list[k].x][list[k].y];

                int tmpIndex = -1;
                if (Board::board[list[k].x][list[k].y] != 0) {
                    for (int j = 0; j < Board::onBoard.size(); j++) {
                        if (Board::onBoard[j]->getX() == list[k].x && Board::onBoard[j]->getY() == list[k].y && Board::onBoard[j]->alive) {
                            Board::onBoard[j]->fakeAlive = false;
                            tmpIndex = j;
                        }
                    }
                }

                Board::onBoard[i]->fakeMove(list[k].x, list[k].y, 0);

                if (!isCheck(0)) {
                    Board::onBoard[i]->fakeMove(Board::onBoard[i]->getX(), Board::onBoard[i]->getY(), col);
                    if (tmpIndex != -1) Board::onBoard[tmpIndex]->fakeAlive = true;
                    Board::clearVirtualMove();
                    return false;
                }
                else {
                    Board::onBoard[i]->fakeMove(Board::onBoard[i]->getX(), Board::onBoard[i]->getY(), col);
                    if (tmpIndex != -1) Board::onBoard[tmpIndex]->fakeAlive = true;
                    Board::clearVirtualMove();
                }
            }
        }
    }
    return true;
}
