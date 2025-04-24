#include <stdio.h>
#include <Windows.h>

// 콘솔 커서 이동 함수
void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

// ANSI 배경 색상 매핑 (0~7)
const char* bgColors[] = {
    "\033[40m", // 0: Black
    "\033[41m", // 1: Red
    "\033[42m", // 2: Green
    "\033[43m", // 3: Yellow
    "\033[44m", // 4: Blue
    "\033[45m", // 5: Magenta
    "\033[46m", // 6: Cyan
    "\033[47m"  // 7: White
};

// 배경과 작업 표시줄을 그리는 함수
void DrawBG(int width, int height) {
    for (int i = 0; i < height; i++) {
        if (i == 0) {
            // 상단 여백
            printf("\n");
        }
        else if (i == height - 1) {
            // 작업 표시줄 (하단 한 줄, 회색 배경)
            printf("  "); // 좌 여백
            for (int j = 0; j < width - 4; j++) {
                printf("\033[100m \033[0m"); // 회색 배경
            }
            printf("  \n"); // 우 여백
        }
        else {
            // 일반 배경 줄 (파란색)
            printf("  "); // 좌 여백
            for (int j = 0; j < width - 4; j++) {
                printf("\033[44m \033[0m"); // 파란 배경
            }
            printf("  \n"); // 우 여백
        }
    }
}

// 콘솔 윈도우 그리기 함수
void drawConsoleWindow(int startX, int startY, int width, int height, const char* title, int color) {
    const char* bg = bgColors[color % 8];

    // 윈도우 내부 영역 그리기
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            gotoxy(startX + x, startY + y);
            printf("%s \033[0m", bg); // 기본 배경
        }
    }

    // 윈도우 테두리 그리기 (흰색)
    for (int x = 0; x < width; x++) {
        // 상단 테두리
        gotoxy(startX + x, startY);
        printf("\033[44m-\033[0m");
        // 하단 테두리
        gotoxy(startX + x, startY + height - 1);
        printf("\033[44m-\033[0m");
    }
    for (int y = 1; y < height - 1; y++) {
        // 좌측 테두리
        gotoxy(startX, startY + y);
        printf("\033[44m|\033[0m");
        // 우측 테두리
        gotoxy(startX + width - 1, startY + y);
        printf("\033[44m|\033[0m");
    }

    // 타이틀 표시 (흰 배경에 검정 글자)
    gotoxy(startX + 2, startY);
    printf("\033[30m\033[47m%s\033[0m", title);

    // X 버튼 (맨 오른쪽 위에 3칸, 빨간 배경에 흰색 텍스트)
    gotoxy(startX + width - 4, startY);
    printf("\033[41m\033[97mX\033[0m");
}

int main() {
    int width = 80;
    int height = 25;

    system("cls");
    DrawBG(width, height); // 배경 + 작업 표시줄 그리기

    // 윈도우 3개 그리기
    drawConsoleWindow(10, 3, 25, 7, "나의 윈도우 1", 3);
    drawConsoleWindow(20, 10, 25, 7, "나의 윈도우 2", 1);
    drawConsoleWindow(35, 5, 25, 7, "나의 윈도우 3", 2);

    gotoxy(0, 25);
    return 0;
}
