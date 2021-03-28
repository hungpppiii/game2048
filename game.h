#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iomanip>

using namespace std;


void startGame();
bool endGame();
//void inTro(int diem);

void left(bool &check);
void right(bool &check);
void up(bool &check);
void down(bool &check);

void hamLeft_Right(const int row, const int col, const int x, bool &check);
void hamUp_Down(const int row, const int col, const int x, bool &check);

void drawTable(int dk);

void khoiTaoBanDau();
bool viTriTrong();
void khoiTaoThemSo();

#endif // GAME_H_INCLUDED
