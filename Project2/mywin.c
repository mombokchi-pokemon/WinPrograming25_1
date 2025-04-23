#include "mywin.h"
#include <stdio.h>
#include <string.h>

void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void clearScreen() {
    system("cls");
}

int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void drawWindow(MyWin* win) {
    if (win->isMax == -1) return;

    printf("\033[%dm", win->color);
    for (int y = win->y; y < win->y + win->height; y++) {
        move_cursor(win->x, y);
        for (int x = 0; x < win->width; x++) {
            printf(" ");
        }
    }
    printf("\033[0m");

    move_cursor(win->x + 2, win->y);
    printf("%s", win->name);
}

int isInside(MyWin* win, int x, int y) {
    return (x >= win->x && x < win->x + win->width &&
        y >= win->y && y < win->y + win->height);
}

int isInsideButton(int btnX, int btnY, int btnW, int btnH, int px, int py) {
    return (px >= btnX && px < btnX + btnW &&
        py >= btnY && py < btnY + btnH);
}

void drawBackground(MyWin* win) {
    printf("\033[%dm", win->color);
    for (int y = win->y + 1; y < win->y + win->height - 1; y++) {
        move_cursor(win->x + 1, y);
        for (int x = 0; x < win->width - 2; x++) {
            printf(" ");
        }
    }
    printf("\033[0m");
}

void drawButtonsText(int x, int y) {
    move_cursor(x, y);
    printf("け置社 け置企");
}
