#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <string>

using namespace std;


const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 700;
const string WINDOW_TITLE = "GAME 2048";

void background();

void drawSquare(const int &so, const int &x, const int &y);

//void updateDisplay();

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);
void initSDL();
void quitSDL();

//****************************************************************
// xóa màn hình và vẽ lại
void refreshScreen(SDL_Window* window, SDL_Renderer* renderer,
    const SDL_Rect& filled_rect, const bool leftMouse = false);

// Hàm nạp texture từ file ảnh, để vẽ lên renderer tương ứng
SDL_Texture* loadTexture(const std::string &file);

// Hàm đưa texture ra renderer (để hiển thị ra màn hình) tại toạ độ (x,y) và thay đổi kích thước ảnh
void renderTexture(SDL_Texture *tex, int x, int y, int w, int h);

#endif // DRAW_H_INCLUDED
