#include <windows.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int x;
    int y;
    int width;
    int height;
    char name[100];
    int color;
    int isMax;
} MyWin;

void move_cursor(int x, int y) {
    printf("\x1b[%d;%dH", y, x);
}

void drawMyWin(MyWin win) {
    int x1, y1, x2, y2;
    if (win.isMax) {
        x1 = 6;
        y1 = 2;
        x2 = getConsoleWidth() - 6;
        y2 = getConsoleHeight() - 4;
    }
    else {
        x1 = win.x;
        y1 = win.y;
        x2 = win.x + win.width;
        y2 = win.y + win.height;
    }

    printf("\x1b[%dm", win.color);
    for (int y = y1; y <= y2; y++) {
        move_cursor(x1, y);
        for (int x = x1; x <= x2; x++) printf(" ");
    }
    printf("\x1b[0m");

    move_cursor(x1 + 2, y1 + 1);
    printf("%s", win.name);
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

int main() {
    MyWin skyWin = { 20, 5, 30, 10, "하늘색 창입니다", 46, 0 }; // 46: Cyan background

    system("cls");
    drawMyWin(skyWin);

    move_cursor(0, getConsoleHeight());
    return 0;
}
