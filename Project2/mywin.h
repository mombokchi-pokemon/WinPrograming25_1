#define MYWIN_H

#include <windows.h>

typedef struct {
    int x, y;
    int width, height;
    char name[100];
    int color;
    int isMax;
} MyWin;

void move_cursor(int x, int y);
void clearScreen();
int getConsoleWidth();
int getConsoleHeight();
void drawWindow(MyWin* win);
int isInside(MyWin* win, int x, int y);
int isInsideButton(int btnX, int btnY, int btnW, int btnH, int px, int py);
void drawBackground(MyWin* win);
void drawButtonsText(int x, int y);