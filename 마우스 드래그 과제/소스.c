#include <windows.h>
#include <stdio.h>

int main(void) {
    char letter = 'O';  // ���ĺ� 'O'
    POINT mousePos;     // ���콺 ��ġ
    int letterX = 10;    // ���ĺ� 'O'�� �ʱ� X ��ǥ
    int letterY = 5;     // ���ĺ� 'O'�� �ʱ� Y ��ǥ

    // �ܼ� ȭ�� �ʱ�ȭ
    system("cls");

    while (1) {
        // ���콺 ���� ��ġ ���
        GetCursorPos(&mousePos);

        // ȭ�� �ʱ�ȭ
        system("cls");  // ȭ�� �����

        // ���콺 Ŭ�� ��ġ�� ǥ��
        printf("���콺 Ŭ�� ��ġ: (%d, %d)\n", mousePos.x / 11, mousePos.y / 21);

        // ���콺 ���� ��ư�� Ŭ���ϸ� ���ĺ� ��ġ ����
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            letterX = mousePos.x / 9;  // ���콺 X ��ġ�� ���ĺ� ��ġ ����
            letterY = mousePos.y / 21; // ���콺 Y ��ġ�� ���ĺ� ��ġ ����
        }

        // ���ĺ� O ���
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { letterX, letterY });
        printf("%c", letter);

        // ���� ����: Q Ű�� ������ ���α׷� ����
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            printf("\n���α׷� ����\n");
            break;
        }

        // ��� ��� (CPU ��� ����ȭ)
        Sleep(10);
    }

    return 0;
}
