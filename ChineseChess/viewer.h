#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QPalette>
#include <QBrush>
#include <QPushButton>
#include <QMouseEvent>
#include <QMessageBox>
#include <QLabel>
#include <QPainter>
#include <QToolTip>
#include <QString>
#include <QFileDialog>
#include <QTimer>
#include <QLCDNumber>

QT_BEGIN_NAMESPACE
namespace Ui { class Viewer; }
QT_END_NAMESPACE

class Viewer : public QWidget
{
    Q_OBJECT

public:
    // Constructor for the Viewer class
    Viewer(QWidget* parent = nullptr);
    ~Viewer();

    // Function to set the initial board
    void setBoard();

    // Function to show the menu
    void menu();

    // Function to update the board after each move
    void paintEvent(QPaintEvent*);

    // Function to handle mouse press events
    void mousePressEvent(QMouseEvent*);

    // Function to handle mouse move events
    void mouseMoveEvent(QMouseEvent*);

    // Function to reset the game
    void reset();

    // Function to update the board after a move
    void afterMove();

public slots:
    // Slot to start the game
    void startGame_slot();

    // Slot to restart the game
    void restartGame_slot(int f = 1);

    // Slot to load a game from a file
    void loadFile_slot();

    // Slot to handle surrender
    void surrender_slot();

    // Slot to save the game
    void saveGame_slot(int f = 1);

    // Slot to handle timeout
    void timeout_slot();

    // Slot to start the game with AI
    void startWithAI_slot();

private:
    Ui::Viewer* ui;

    // Buttons for various actions
    QPushButton* startBtn;
    QPushButton* quitBtn;
    QPushButton* restartBtn;
    QPushButton* loadBtn;
    QPushButton* surrenderBtn;
    QPushButton* saveGameBtn;
    QPushButton* aiBtn;

    // Labels for displaying information
    QLabel* title1;
    QLabel* click_label;
    QLabel* nowPlayer_label;
    QLabel* time_label;
    QLabel* checkKing_label;
    QLabel* gameMode_label;

    // Timer for the game
    QTimer* timer;

    // Flags to indicate the game state
    bool start = false;
    bool ai = false;

    // Variables to store the click position
    int xPos = 10, yPos = 10;

    // Counter for the timer
    int counter = 0;
    const int setTime = 40;
};

#endif // VIEWER_H
