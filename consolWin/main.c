#include <Windows.h>
#include <stdio.h>

// 콘솔 화면에서 커서를 (x, y) 위치로 이동시키는 함수
void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, Cur);
}

// 윈도우 정보 구조체 정의
typedef struct {
	int startX;  // 윈도우 x 시작 위치
	int startY; // 윈도우 y 시작 위치
	const char* windowName;  //윈도우 이름
	const char* windowColor;  //윈도우 색상 
} windowInfo;

// 윈도우 개수 정의
#define numWindows 3

// 구조체 배열 정의
windowInfo windows[numWindows] = {
	{10, 3, "나의 윈도우 1", "\033[43m"},  //노란색
	{15, 5, "나의 윈도우 2",  "\033[41m"},  // 빨간색
	{40, 7, "나의 윈도우 3",  "\033[44m"},  // 파란색
};

// 윈도우 그리기 함수
int drawWindow(windowInfo* win) {
	int width = 20;
	int height = 7;

	// 흰 화면 그리기
	for (int x = 1; x < width; x++) {
		for (int y = 1; y < height; y++) {
			gotoxy(win->startX + x, win->startY + y);
			printf("\033[47m ");
		}

	}

	// 윈도우 이름 쓰기
	gotoxy(win->startX + 1, win->startY + 1);
	printf("\033[30m\033[47m%s", win->windowName);

    // 가로 테두리 선 그리기
	for (int x = 0; x < width; x++) {
		gotoxy(win->startX + x, win->startY);  // 윗줄
		printf("%s ", win->windowColor);

		gotoxy(win->startX + x, win->startY + 2);  // 중간줄
		printf("%s ", win->windowColor);

		gotoxy(win->startX + x, win->startY + height - 1);  // 아랫줄
		printf("%s ", win->windowColor);
	}
		
    // 세로 테두리 선 그리기
	for (int y = 1; y < height - 1; y++) {
		gotoxy(win->startX, win->startY + y);  // 왼쪽 세로선
		printf("%s ", win->windowColor);

		gotoxy(win->startX + width - 1, win->startY + y);  // 오른쪽 세로선
		printf("%s \033[0m", win->windowColor);
	}
    return 0;
}

//배경 그리기 함수
int drawBackground() {
	for (int i = 0; i < 29; i++) {
		puts("\033[32m\033[42m배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면\033[0m");
	}
	return 0;
}

int main() {
	drawBackground();  // 배경 생성 함수 호출

	for (int i = 0; i < numWindows; ++i) {  // 윈도우 생성 함수 호출
		drawWindow(&windows[i]);
	}

	gotoxy(0, 29);
	return 0;
}