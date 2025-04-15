#include <windows.h>
#include <stdio.h>

int main() {
    char letter = 'O';  // 알파벳 'O' 고정
    POINT mousePos = { 0, 0 };     // 마우스 위치 (초기화
    int isDragging = 0;  // 드래그 상태 (0: 드래그 중 아님, 1: 드래그 중)
    int letterX = 10;    // 알파벳 'O'의 초기 X 좌표
    int letterY = 5;     // 알파벳 'O'의 초기 Y 좌표
    int dragRange = 2;   // 드래그 시작이 가능한 허용 범위 추가함. (상하좌우 2 텍스트 셀 이내)

    while (1) {
        // 화면 갱신
        system("cls");  // 화면 초기화
        printf("알파벳 '%c'을 마우스로 드래그하세요.\n", letter);
        printf("현재 알파벳 '%c'의 위치: (%d, %d)\n", letter, letterX, letterY);

        // 알파벳 O 출력
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { letterX, letterY });
        printf("%c", letter);

        // 현재 마우스 상태 가져오기
        if (GetCursorPos(&mousePos)) {
            // 마우스 왼쪽 버튼 클릭 상태 확인
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                // 문자 근처에 있을 때 드래그 시작
                int mouseX = mousePos.x / 9;
                int mouseY = mousePos.y / 19 - 2;  // -2는 타이틀 바를 고려한 위치 조정

                if (!isDragging &&
                    mouseX >= (letterX - dragRange) && mouseX <= (letterX + dragRange) &&
                    mouseY >= (letterY - dragRange) && mouseY <= (letterY + dragRange)) {
                    isDragging = 1; // 드래그 시작
                }
            }
            else {
                isDragging = 0; // 드래그 중지
            }

            // 드래그 중일 때 문자 위치 업데이트
            if (isDragging) {
                letterX = mousePos.x / 9;
                letterY = mousePos.y / 19 - 2;  // -2는 타이틀 바를 고려한 위치 조정
            }
        }

        // 종료 조건: ESC 키를 누르면 프로그램 종료
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            printf("\n프로그램 종료\n");
            break;
        }

        // 잠시 대기 (CPU 사용 최적화)
        Sleep(10);
    }

    return 0;
}

