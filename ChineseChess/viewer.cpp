// 定位: 25+56*x ,25+56*y
// 棋子大小: 50*50

#include "viewer.h"
#include "ui_viewer.h"
#include "GameManager.h"
#include "Board.h"
#include <iostream>

// Constructor for the Viewer class
Viewer::Viewer(QWidget *parent)
    : QWidget(parent), ui(new Ui::Viewer)
{
    ui->setupUi(this);
    setWindowTitle("Chinese Chess");
    setWindowIcon(QIcon(":/ChineseChess/img/icon.png"));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout_slot()));
    timer->stop();
}

// Destructor for the Viewer class
Viewer::~Viewer()
{
    delete ui;
}

// Function to show the menu
void Viewer::menu()
{
    start = false;
    ai = false;
    timer->stop();

    Board::clearMove();
    setFixedSize(300, 300);

    title1 = new QLabel(" Chinese Chess", this);
    title1->setFont(QFont("Black font of Microsoft", 20));
    title1->setGeometry(90, 20, 150, 30);

    startBtn = new QPushButton(" Start new game", this);
    startBtn->setGeometry(90, 80, 120, 40);
    startBtn->setFlat(0);

    loadBtn = new QPushButton(" Continue", this);
    loadBtn->setGeometry(90, 130, 120, 40);
    loadBtn->setFlat(0);

    aiBtn = new QPushButton(" Human - Machine", this);
    aiBtn->setGeometry(90, 180, 120, 40);
    aiBtn->setFlat(0);

    quitBtn = new QPushButton(" Exit", this);
    quitBtn->setGeometry(90, 230, 120, 40);
    quitBtn->setFlat(0);

    title1->show();
    startBtn->show();
    loadBtn->show();
    quitBtn->show();
    aiBtn->show();

    GameManager::restartGame();

    connect(startBtn, SIGNAL(clicked(bool)), this, SLOT(startGame_slot()));
    connect(quitBtn, SIGNAL(clicked(bool)), qApp, SLOT(quit()));
    connect(loadBtn, SIGNAL(clicked(bool)), this, SLOT(loadFile_slot()));
    connect(aiBtn, SIGNAL(clicked(bool)), this, SLOT(startWithAI_slot()));
}

// Set the initial board
void Viewer::setBoard()
{
    setFixedSize(700, 598);

    timer->start(1000);

    gameMode_label = new QLabel(" ", this);
    gameMode_label->setFont(QFont("Black font of Microsoft", 15));
    gameMode_label->setGeometry(40, 1, 200, 30);
    if (ai)
        gameMode_label->setText("Mod: Human-Machine");
    else
        gameMode_label->setText("Mode: Human-Human");

    click_label = new QLabel(" ", this);
    click_label->setFont(QFont("Black font of Microsoft", 15));
    click_label->setGeometry(1, 1, 150, 30);

    time_label = new QLabel(" ", this);
    time_label->setFont(QFont("Black font of Microsoft", 15));
    time_label->setGeometry(556, 5, 150, 30);

    checkKing_label = new QLabel(" ", this);
    checkKing_label->setFont(QFont("Black font of Microsoft", 25));
    checkKing_label->setGeometry(550, 300, 150, 120);
    if (ai)
        checkKing_label->setText(QString(" "));

    nowPlayer_label = new QLabel(" ", this);
    if (GameManager::currentPlayer % 2 == 0)
    {
        nowPlayer_label->setText(QString("Your turn\n Red side"));
    }
    else
    {
        nowPlayer_label->setText(QString("Your turn\n Black side"));
    }
    nowPlayer_label->setFont(QFont("Black font of Microsoft", 15));
    nowPlayer_label->setGeometry(585, 40, 120, 60);

    restartBtn = new QPushButton(" Restart game", this);
    restartBtn->setGeometry(565, 120, 120, 40);
    restartBtn->setFlat(0);
    restartBtn->show();

    surrenderBtn = new QPushButton(" GG!", this);
    surrenderBtn->setGeometry(565, 180, 120, 40);
    surrenderBtn->setFlat(0);
    surrenderBtn->show();

    saveGameBtn = new QPushButton(" Save game", this);
    saveGameBtn->setGeometry(565, 240, 120, 40);
    saveGameBtn->setFlat(0);
    surrenderBtn->show();

    update();

    connect(restartBtn, SIGNAL(clicked(bool)), this, SLOT(restartGame_slot()));
    connect(surrenderBtn, SIGNAL(clicked(bool)), this, SLOT(surrender_slot()));
    connect(saveGameBtn, SIGNAL(clicked(bool)), this, SLOT(saveGame_slot()));
}

// Function to update the board after each move
void Viewer::paintEvent(QPaintEvent *)
{
    if (start)
    {
        QPainter painter(this);

        painter.drawPixmap(QRect(0, 0, 550, 598), QPixmap(":/ChineseChess/img/Board-4.jpg"));

        if (xPos < 9 && yPos < 10)
        {
            painter.drawPixmap(QRect(25 + 56 * xPos, 25 + 56 * yPos, 50, 50), QPixmap(":/ChineseChess/img/select.png"));
        }

        // Mark out a movable position
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (Board::move[i][j] == 1)
                {
                    painter.drawPixmap(QRect(25 + 56 * i, 25 + 56 * j, 50, 50), QPixmap(":/ChineseChess/img/canMove.png"));
                }
            }
        }

        // Draw all the pieces on the board
        for (int i = 0; i < Board::onBoard.size(); i++)
        {
            if (Board::onBoard[i]->alive)
            {
                int tx = Board::onBoard[i]->getX();
                int ty = Board::onBoard[i]->getY();
                QString pic = QString::fromStdString(Board::onBoard[i]->getPic());
                painter.drawPixmap(QRect(25 + 56 * tx, 25 + 56 * ty, 50, 50), QPixmap(pic));
            }
        }

        update();
    }
}

// Function to handle mouse press events
void Viewer::mousePressEvent(QMouseEvent *pos)
{
    if (start)
    {
        pos->globalPos();

        if (pos->x() >= 25 && pos->y() >= 25)
        {
            if ((((pos->x() - 25) / 56) <= 8) && (((pos->y() - 25) / 56) <= 9))
            {
                xPos = (pos->x() - 25) / 56;
                yPos = (pos->y() - 25) / 56;
            }
        }
        click_label->setText(QString("%1, %2").arg(xPos).arg(yPos));

        static int press = 0;
        static int index = -1;
        static int nx, ny;
        static int tmpX, tmpY;
        int nowPlayer = GameManager::currentPlayer % 2;

        if (nowPlayer == 0)
            nowPlayer = 1;
        else if (nowPlayer == 1)
            nowPlayer = -1;

        if (press == 1)
        {
            nx = xPos;
            ny = yPos;
            press++;
        }
        else if (press == 0)
        {
            for (int i = 0; i < Board::onBoard.size(); i++)
            {
                tmpX = Board::onBoard[i]->getX();
                tmpY = Board::onBoard[i]->getY();

                if (xPos == tmpX && yPos == tmpY && Board::onBoard[i]->alive && nowPlayer == Board::onBoard[i]->color)
                {
                    Board::onBoard[i]->canMove(0);
                    index = i;
                    press++;
                    break;
                }
            }
        }
        if (press == 2)
        {
            press = 0;
            if (Board::board[nx][ny] == 0 && Board::move[nx][ny] == 1)
            {
                Board::onBoard[index]->move(nx, ny);
                Board::onBoard[index]->makeLog(tmpX, tmpY);
                afterMove();
                Board::clearMove();
                xPos = 10;
                yPos = 10;

                if (ai && GameManager::currentPlayer % 2 == 1)
                {
                    GameManager::aiGame();
                    if (GameManager::currentPlayer % 2 == 0)
                    {
                        nowPlayer_label->setText(QString("Your turn\n Red side"));
                    }
                    else
                    {
                        nowPlayer_label->setText(QString("Your turn\n Black side"));
                    }
                }
            }
            else if (Board::board[nx][ny] == Board::onBoard[index]->color * -1)
            {
                if (Board::move[xPos][yPos] == 1)
                {
                    for (int i = 0; i < Board::onBoard.size(); i++)
                    {
                        int tx = Board::onBoard[i]->getX();
                        int ty = Board::onBoard[i]->getY();

                        if (nx == tx && ny == ty && Board::onBoard[i]->alive)
                        {
                            Board::onBoard[i]->alive = false;
                            Board::onBoard[i]->fakeAlive = false;
                        }
                    }
                    Board::onBoard[index]->move(nx, ny);
                    Board::onBoard[index]->makeLog(tmpX, tmpY);
                    afterMove();
                }
                Board::clearMove();
                xPos = 10;
                yPos = 10;
                if (ai && GameManager::currentPlayer % 2 == 1)
                {
                    GameManager::aiGame();
                    if (GameManager::currentPlayer % 2 == 0)
                    {
                        nowPlayer_label->setText(QString("your turn\n red side"));
                    }
                    else
                    {
                        nowPlayer_label->setText(QString("your turn\n black side"));
                    }
                }
            }
            else
            {
                Board::clearMove();
                for (int i = 0; i < Board::onBoard.size(); i++)
                {
                    tmpX = Board::onBoard[i]->getX();
                    tmpY = Board::onBoard[i]->getY();

                    if (xPos == tmpX && yPos == tmpY && Board::onBoard[i]->alive)
                    {
                        Board::onBoard[i]->canMove(0);
                        index = i;
                        press++;
                        break;
                    }
                }
            }
        }

        Board::clearVirtualMove();
        if (GameManager::isCheck(1))
        {
            checkKing_label->setText(QString("<font color=red> Checkmate</font>"));
        }
        else
        {
            checkKing_label->setText(QString(" "));
        }
        Board::clearVirtualMove();
    }
}

// Function to handle mouse move events
void Viewer::mouseMoveEvent(QMouseEvent *pos)
{
    update();
    QToolTip::showText(pos->globalPos(), QString("%1, %2").arg(pos->x()).arg(pos->y()));
}

// Slot to start the game
void Viewer::startGame_slot()
{
    xPos = 10;
    yPos = 10;
    setBoard();
    start = true;
    title1->hide();
    startBtn->hide();
    loadBtn->hide();
    quitBtn->hide();
    aiBtn->hide();

    time_label->show();
    checkKing_label->show();

    gameMode_label->show();
    time_label->setText(QString("<font color=black>remaining: \n %1 s</font>").arg(setTime));
    counter = -1;

    click_label->show();
    nowPlayer_label->show();
    surrenderBtn->show();
    saveGameBtn->show();
    timer->start(1000);
    checkKing_label->show();
}

// Function to reset the game
void Viewer::reset()
{
    if (!(QMessageBox::information(this, tr("Info"), tr("restart?"), tr("restart"), tr("home"))))
    {
        counter = -1;
        GameManager::restartGame();
        if (GameManager::currentPlayer % 2 == 0)
        {
            nowPlayer_label->setText(QString("your turn\n red side"));
        }
        else
        {
            nowPlayer_label->setText(QString("your turn\n black side"));
        }
        timer->start(1000);
        counter = -1;
    }
    else
    {
        menu();
        click_label->hide();
        time_label->hide();
        checkKing_label->hide();
        checkKing_label->setText(QString(" "));
        gameMode_label->hide();
        nowPlayer_label->hide();
    }
}

// Function to update the board after a move
void Viewer::afterMove()
{
    counter = -1;
    timer->stop();
    timer->start(1000);

    if (!GameManager::checkKing())
    {
        timer->stop();
        QMessageBox msg;
        if (GameManager::currentPlayer % 2 == 0)
        {
            msg.setText("black side wins!");
        }
        else
        {
            msg.setText("red side wins!");
        }
        msg.exec();
        saveGame_slot(0);
        reset();
    }

    if (GameManager::currentPlayer % 2 == 0)
    {
        nowPlayer_label->setText(QString("your turn\n red side"));
    }
    else
    {
        nowPlayer_label->setText(QString("your turn\n black side"));
    }

    Board::clearVirtualMove();
    if (GameManager::stalemate() && start)
    {
        timer->stop();
        QMessageBox msg;
        if (GameManager::currentPlayer % 2 == 0)
        {
            msg.setText("red side stalemate, black side wins!");
        }
        else
        {
            msg.setText("black side stalemate, red side wins!");
        }
        msg.exec();
        saveGame_slot(0);
        reset();
    }
    Board::clearVirtualMove();
}

// Slot to restart the game
void Viewer::restartGame_slot(int f)
{
    timer->stop();
    if (!(QMessageBox::information(this, tr("Warning"), tr(" restart the game?"), tr("Yes"), tr("No"))))
    {
        counter = -1;
        saveGame_slot();
        GameManager::restartGame();
        if (GameManager::currentPlayer % 2 == 0)
        {
            nowPlayer_label->setText(QString("your turn\n red side"));
        }
        else
        {
            nowPlayer_label->setText(QString("your turn\n black side"));
        }
        timer->start(1000);
    }
    else
    {
        if (f == 1)
            timer->start(1000);
    }
}

// Slot to load a game from a file
void Viewer::loadFile_slot()
{
    GameManager::restartGame();
    QString filePath = QFileDialog::getOpenFileName(NULL, QObject::tr("Open File"),
                                                    qApp->applicationDirPath(), QObject::tr("Text (*.txt)"));

    GameManager::loadFile(filePath.toStdString());
    cout << filePath.toStdString() << endl;

    if (filePath != "")
    {
        QMessageBox msg;
        msg.setText("Load File Success!");
        startGame_slot();
        msg.exec();
        afterMove();
        Board::clearMove();
    }
}

// Slot to handle surrender
void Viewer::surrender_slot()
{
    timer->stop();
    if (!(QMessageBox::information(this, tr("Warning"), tr("GG?"), tr("Yes"), tr("No"))))
    {
        QMessageBox msg;
        if (GameManager::currentPlayer % 2 == 0)
        {
            msg.setText("black side wins!");
        }
        else
        {
            msg.setText("red side wins!");
        }
        msg.exec();
        saveGame_slot(0);
        reset();
    }
    else
    {
        timer->start(1000);
    }
}

// Slot to save the game
void Viewer::saveGame_slot(int f)
{
    timer->stop();
    if (!(QMessageBox::information(this, tr("Warning"), tr("save the game?"), tr("Yes"), tr("No"))))
    {
        QDateTime time = QDateTime::currentDateTime();
        QString str = time.toString("yyyy-MM-dd_hh-mm-ss");
        string path = "save\\" + str.toStdString() + ".txt";
        string command = "copy log.txt " + path;
        cout << command << endl;
        system(command.c_str());
        QMessageBox msg;
        msg.setText("save completed！\n saved to：\nfolder\\save\\" + str + ".txt");
        msg.exec();
        timer->start(1000);
    }
    else
    {
        if (f == 1)
            timer->start(1000);
        else if (start && f != 0)
            timer->start(1000);
    }
}

// Slot to handle timeout
void Viewer::timeout_slot()
{
    if (counter == setTime)
    {
        QMessageBox::warning(this, "timer", QString("time's up"));
        timer->stop();
        QMessageBox msg;
        if (GameManager::currentPlayer % 2 == 0)
        {
            msg.setText("black side wins!");
        }
        else
        {
            msg.setText("red side wins!");
        }
        msg.exec();
        saveGame_slot(0);
        reset();
    }
    else
    {
        counter++;
        if (setTime - counter < 10)
        {
            time_label->setText(QString("<font color=red>time left: %1 s</font>").arg(setTime - counter));
        }
        else
        {
            time_label->setText(QString("<font color=black>time left: %1 s</font>").arg(setTime - counter));
        }
    }
}

// Slot to start the game with AI
void Viewer::startWithAI_slot()
{
    GameManager::restartGame();
    ai = true;
    startGame_slot();
    GameManager::currentPlayer = 0;
}
