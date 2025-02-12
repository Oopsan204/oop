//#include "viewer.h"
#include "GameManager.h"
#include "Board.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    // Initialize the Qt application
    QApplication a(argc, argv);
    GameManager game;

    // Initialize chess pieces with their positions, colors, and image sources
    King ch04(4, 0, -1, ":/ChineseChess/img/B_jiang.png");
    King ch05(4, 9, 1, ":/ChineseChess/img/R_jiang.png");
    Advisor ch06(3, 0, -1, ":/ChineseChess/img/B_shi.png");
    Advisor ch07(5, 0, -1, ":/ChineseChess/img/B_shi.png");
    Advisor ch08(3, 9, 1, ":/ChineseChess/img/R_shi.png");
    Advisor ch09(5, 9, 1, ":/ChineseChess/img/R_shi.png");
    Minister ch10(2, 0, -1, ":/ChineseChess/img/B_siang.png");
    Minister ch11(6, 0, -1, ":/ChineseChess/img/B_siang.png");
    Minister ch12(2, 9, 1, ":/ChineseChess/img/R_siang.png");
    Minister ch13(6, 9, 1, ":/ChineseChess/img/R_siang.png");
    Horse ch14(1, 0, -1, ":/ChineseChess/img/B_ma.png");
    Horse ch15(7, 0, -1, ":/ChineseChess/img/B_ma.png");
    Horse ch16(1, 9, 1, ":/ChineseChess/img/R_ma.png");
    Horse ch17(7, 9, 1, ":/ChineseChess/img/R_ma.png");
    Soldier ch18(0, 3, -1, ":/ChineseChess/img/B_bing.png");
    Soldier ch19(2, 3, -1, ":/ChineseChess/img/B_bing.png");
    Soldier ch20(4, 3, -1, ":/ChineseChess/img/B_bing.png");
    Soldier ch21(6, 3, -1, ":/ChineseChess/img/B_bing.png");
    Soldier ch22(8, 3, -1, ":/ChineseChess/img/B_bing.png");
    Soldier ch23(0, 6, 1, ":/ChineseChess/img/R_bing.png");
    Soldier ch24(2, 6, 1, ":/ChineseChess/img/R_bing.png");
    Soldier ch25(4, 6, 1, ":/ChineseChess/img/R_bing.png");
    Soldier ch26(6, 6, 1, ":/ChineseChess/img/R_bing.png");
    Soldier ch27(8, 6, 1, ":/ChineseChess/img/R_bing.png");
    Chariot ch28(0, 0, -1, ":/ChineseChess/img/B_che.png");
    Chariot ch29(8, 0, -1, ":/ChineseChess/img/B_che.png");
    Chariot ch30(0, 9, 1, ":/ChineseChess/img/R_che.png");
    Chariot ch31(8, 9, 1, ":/ChineseChess/img/R_che.png");
    Cannon ch32(1, 2, -1, ":/ChineseChess/img/B_pao.png");
    Cannon ch33(7, 2, -1, ":/ChineseChess/img/B_pao.png");
    Cannon ch34(1, 7, 1, ":/ChineseChess/img/R_pao.png");
    Cannon ch35(7, 7, 1, ":/ChineseChess/img/R_pao.png");

    // Set the pointers to the kings
    Board::BKing = &ch04;
    Board::RKing = &ch05;

    // Add the chess pieces to the game
    game.pushIn(&ch04);
    game.pushIn(&ch05);
    game.pushIn(&ch06);
    game.pushIn(&ch07);
    game.pushIn(&ch08);
    game.pushIn(&ch09);
    game.pushIn(&ch10);
    game.pushIn(&ch11);
    game.pushIn(&ch12);
    game.pushIn(&ch13);
    game.pushIn(&ch14);
    game.pushIn(&ch15);
    game.pushIn(&ch16);
    game.pushIn(&ch17);
    game.pushIn(&ch18);
    game.pushIn(&ch19);
    game.pushIn(&ch20);
    game.pushIn(&ch21);
    game.pushIn(&ch22);
    game.pushIn(&ch23);
    game.pushIn(&ch24);
    game.pushIn(&ch25);
    game.pushIn(&ch26);
    game.pushIn(&ch27);
    game.pushIn(&ch28);
    game.pushIn(&ch29);
    game.pushIn(&ch30);
    game.pushIn(&ch31);
    game.pushIn(&ch32);
    game.pushIn(&ch33);
    game.pushIn(&ch34);
    game.pushIn(&ch35);

    // Show the game menu
    game.showMenu();

    // Execute the Qt application
    return a.exec();
}
