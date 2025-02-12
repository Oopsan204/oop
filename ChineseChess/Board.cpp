#include "Board.h"

// Vector to store all chess pieces currently on the board
vector<Chess*> Board::onBoard;

// 2D arrays to represent the board state, possible moves, and virtual moves
int Board::board[9][10] = { };
int Board::move[9][10] = { };
int Board::virtualMove[9][10] = { };

// Pointers to the red and black kings on the board
Chess* Board::RKing = nullptr;
Chess* Board::BKing = nullptr;

// Function to add a chess piece to the board
void Board::pushIn(Chess* ch)
{
	// Add the chess piece to the onBoard vector
	Board::onBoard.push_back(ch);
	// Update the board array with the piece's color at its position
    Board::board[ch->getX()][ch->getY()] = ch->color;
}

// Function to print the current state of the board
void Board::printBoard()
{
	// Iterate through each row of the board
	for (int i = 0; i < 10; i++) {
		// Print a newline after the fifth row for better readability
		if (i == 5) cout << "\n";
		// Iterate through each column of the board
		for (int j = 0; j < 9; j++) {
			// Print the value at the current position
            cout << board[j][i] << " ";
		}
		// Print a newline at the end of each row
		cout << endl;
	}
	// Print a separator line
	cout << "------------------------------\n";
}

// Function to reset the board to its initial state
void Board::resetBoard()
{
	// Iterate through each position on the board
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			// Set each position to 0 (empty)
			Board::board[i][j] = 0;
		}
	}
	// Iterate through each chess piece on the board
	for (int i = 0; i < Board::onBoard.size(); i++) {
		// Set the piece's alive and fakeAlive status to false
		Board::onBoard[i]->alive = false;
		Board::onBoard[i]->fakeAlive = false;
	}
}

// Function to clear the move array
void Board::clearMove()
{
	// Iterate through each position in the move array
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			// Set each position to 0 (no move)
			Board::move[i][j] = 0;
		}
	}
}

// Function to print the current state of the move array
void Board::printMove()
{
	// Iterate through each row of the move array
	for (int i = 0; i < 10; i++) {
		// Print a newline after the fifth row for better readability
		if (i == 5) cout << "\n";
		// Iterate through each column of the move array
		for (int j = 0; j < 9; j++) {
			// Print the value at the current position
			cout << move[j][i] << " ";
		}
		// Print a newline at the end of each row
		cout << endl;
	}
}

// Function to clear the virtual move array
void Board::clearVirtualMove()
{
	// Iterate through each position in the virtual move array
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			// Set each position to 0 (no virtual move)
			Board::virtualMove[i][j] = 0;
		}
	}
}

// Function to print the current state of the virtual move array
void Board::printVirtualMove()
{
	// Print a header for the virtual move array
	cout << "virtual:\n";
	// Iterate through each row of the virtual move array
	for (int i = 0; i < 10; i++) {
		// Print a newline after the fifth row for better readability
		if (i == 5) cout << "\n";
		// Iterate through each column of the virtual move array
		for (int j = 0; j < 9; j++) {
			// Print the value at the current position
			cout << virtualMove[j][i] << " ";
		}
		// Print a newline at the end of each row
		cout << endl;
	}
	// Print an additional newline at the end
	cout << endl;
}