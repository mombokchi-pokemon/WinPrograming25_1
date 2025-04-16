#include <windows.h>
#include <stdio.h>

int main(void) {
    char letter = 'O';  // 알파벳 'O'
    POINT mousePos;     // 마우스 위치
    int letterX = 10;    // 알파벳 'O'의 초기 X 좌표
    int letterY = 5;     // 알파벳 'O'의 초기 Y 좌표

    // 콘솔 화면 초기화
    system("cls");

    while (1) {
        // 마우스 현재 위치 얻기
        GetCursorPos(&mousePos);

        // 화면 초기화
        system("cls");  // 화면 지우기

        // 마우스 클릭 위치를 표시
        printf("마우스 클릭 위치: (%d, %d)\n", mousePos.x / 11, mousePos.y / 21);

        // 마우스 왼쪽 버튼을 클릭하면 알파벳 위치 갱신
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            letterX = mousePos.x / 9;  // 마우스 X 위치로 알파벳 위치 갱신
            letterY = mousePos.y / 21; // 마우스 Y 위치로 알파벳 위치 갱신
        }

        // 알파벳 O 출력
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { letterX, letterY });
        printf("%c", letter);

        // 종료 조건: Q 키를 누르면 프로그램 종료
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            printf("\n프로그램 종료\n");
            break;
        }

        // 잠시 대기 (CPU 사용 최적화)
        Sleep(10);
    }

    return 0;
}
