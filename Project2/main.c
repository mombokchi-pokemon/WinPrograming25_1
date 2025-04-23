#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "mywin.h"

int main() {
    POINT mouse;

    MyWin desktop = { 5, 1, getConsoleWidth() - 10, getConsoleHeight() - 4, "Desktop", 44, 0 };
    MyWin boxA = { 15, 6, 30, 10, "Box 1", 45, 0 };
    MyWin boxB = { 50, 12, 25, 8, "Box 2", 42, 0 };

    MyWin* front = &boxA;
    MyWin* back = &boxB;
    MyWin* draggingBox = NULL;
    MyWin* selectedBox = NULL;

    int offsetX = 0, offsetY = 0;
    int wasDown = 0;

    int btnX = desktop.x + desktop.width - 20;
    int btnY = desktop.y + 2; // 버튼 위치 한 줄 아래로 내림
    int btnMinWidth = strlen("ㅁ최소");
    int btnMaxWidth = strlen("ㅁ최대");

    while (1) {
        GetCursorPos(&mouse);
        int cx = mouse.x / 9;
        int cy = mouse.y / 19;
        int isDown = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);

        if (isInside(front, cx, cy)) {
            selectedBox = front;
        }
        else if (isInside(back, cx, cy)) {
            selectedBox = back;
        }
        else {
            selectedBox = NULL;
        }

        if (isDown && !wasDown) {
            if (isInsideButton(btnX, btnY, btnMinWidth, 1, cx, cy)) {
                if (selectedBox) selectedBox->isMax = -1;
            }
            else if (isInsideButton(btnX + btnMinWidth + 1, btnY, btnMaxWidth, 1, cx, cy)) {
                if (selectedBox) {
                    selectedBox->isMax = 0;
                    if (selectedBox == &boxA) {
                        selectedBox->x = 15; selectedBox->y = 6;
                        selectedBox->width = 30; selectedBox->height = 10;
                    }
                    else if (selectedBox == &boxB) {
                        selectedBox->x = 50; selectedBox->y = 12;
                        selectedBox->width = 25; selectedBox->height = 8;
                    }
                }
            }
            else {
                if (front->isMax != -1 && isInside(front, cx, cy)) {
                    draggingBox = front;
                    offsetX = cx - front->x;
                    offsetY = cy - front->y;
                }
                else if (back->isMax != -1 && isInside(back, cx, cy)) {
                    MyWin* temp = front;
                    front = back;
                    back = temp;
                    draggingBox = front;
                    offsetX = cx - front->x;
                    offsetY = cy - front->y;
                }
            }
        }

        if (isDown && draggingBox && draggingBox->isMax != -1) {
            draggingBox->x = cx - offsetX;
            draggingBox->y = cy - offsetY;
        }

        if (!isDown) draggingBox = NULL;
        wasDown = isDown;

        clearScreen();
        move_cursor(cx, cy);
        printf("O");

        drawWindow(&desktop);
        drawBackground(&desktop);
        drawButtonsText(btnX, btnY);

        drawWindow(back);
        drawWindow(front);

        Sleep(10);
    }

    return 0;
}