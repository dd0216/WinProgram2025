#include <Windows.h>
#include <stdio.h>

// 콘솔 화면에서 커서를 (x, y) 위치로 이동시키는 함수
void gotoxy(int x, int y) {  // (Windows.h의 함수(기능) 두개를 포함하여 만듬!)
    COORD Cur;  // (코디네이트(좌표) 구조체로, 이미 Windows 헤더파일에 정의되어 있는 표준 구조체임.)
    Cur.X = x;  // (좌표 구조체 변수에 커서의 x 위치 할당)
    Cur.Y = y;  // (좌표 구조체 변수에 커서의 y 위치 할당)
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);  // (콘솔의 표준 출력 핸들을 가져오는 Windows API 함수를 사용!)
    SetConsoleCursorPosition(output, Cur);  // (지정된 콘솔 핸들(output)에서 커서를 좌표 구조체(Cur)가 가리키는 위치로 이동시키는 Windows API 함수)
}

// 윈도우 정보 구조체 정의
typedef struct {
    int startX;  // 윈도우 x 시작 위치
    int startY;  // 윈도우 y 시작 위치 
    const char* windowName;  // 윈도우 이름 (이름과 색깔은 함수내에서 변하지 않으므로 (읽기 전용) 상수 문자열 정보 저장 변수로 만들어야 함. 구조체 내에서 문자열 리터럴을 사용하는 경우 반드시 const char*를 사용! (char*은 동적 메모리 문자열 저장 시))
    const char* windowColor;   // 윈도우 색상 (const char*은 주소만 저장하고 포인터로 문자열 리터럴의 주소를 가리킴. *는 포인터를 나타냄. 이게 없으면 주소 참조 불가해서 코드 작동안함.)
} windowInfo;

// 윈도우 개수 정의
#define numWindows 3  // (배열 크기를 #define으로 정의하여 상수 초기화 문제 해결! numWindows 라는 상수를 정의해 윈도우 개수 미리 정해주기)

// 구조체 배열 선언 (정적으로 초기화)
windowInfo windows[numWindows] = {  // (윈도우 정보 구조체를 windows 배열로 정의)
   {10, 3, "나의 윈도우 1", "\033[43m"},  //노란색
   {15, 5, "나의 윈도우 2",  "\033[41m"},  // 빨간색
   {40, 7, "나의 윈도우 3",  "\033[44m"},  // 파란색
};

// 윈도우 그리기 함수
int drawWindow(windowInfo* win) {  //
    int width = 20;
    int height = 7;

    // 흰 화면 그리기
    for (int x = 1; x < width; x++) {
        for (int y = 1; y < height; y++) {
            gotoxy(win->startX + x, win->startY + y);
            printf("\033[47m ");  // 흰색 배경색으로 윈도우 배경 칠하기
        }

    }

    // 윈도우 이름 쓰기
    gotoxy(win->startX + 1, win->startY + 1);
    printf("\033[30m\033[47m%s", win->windowName);  // 검은색 글자색과 흰색 배경색으로 윈도우 이름 쓰기

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
        puts("\033[32m\033[42m배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면배경화면\033[0m");  // (pu)
    }
    return 0;
}

int main() {
    drawBackground();  // 배경 생성 함수 호출

    for (int i = 0; i < numWindows; ++i) {  // 윈도우 생성 함수 호출
        drawWindow(&windows[i]);  // (windows 배열의 첫번째 인덱스인 window[0]의 주소부터 [i]번째 주소까지 전달)
    }

    gotoxy(0, 29);
    return 0;
}



/* 프로그램 작성 (코드 구현) 순서

1. 기본적으로 필요한 함수 작성
커서 이동 함수 gotoxy() 구현 (Windows API에 정의된 좌표 구조체, 콘솔 출력 핸들 함수를 사용해 콘솔 화면의 특정 위치로 커서 이동하게 만드는 함수 작성.)

2. 구조체 정의 및 초기화
윈도우 정보를 담을 구조체 windowInfo 작성. (윈도우의 x시작위치, y시작위치, 이름, 색상을 저장)
구조체 배열 초기화로 필요한 윈도우 데이터를 윈도우 창 개수만큼 미리 설정. (구조체 배열을 선언 및 정의)

3. 윈도우 그리기 함수 작성
drawWindow() 작성:
윈도우  흰색 바탕과 윈도우 색상 테두리를 출력.
구조체 포인터를 사용하여 윈도우 정보 접근.

4. 배경 그리기 함수 작성
drawBackground() 작성:
콘솔 화면을 초록색 배경 색상으로 채우기.

5. 메인 함수 작성
각 기능 호출:
-> 배경 생성 호출
-> 윈도우 생성 호출.
-> 커서 맨아래로 옮긴 후 프로그램 종료.

배울 수 있는 것들:
- Windows API와 콘솔 출력 처리 방법
- 구조체 배열을 활용한 데이터 관리
- ANSI 코드로 콘솔 출력 색상 제어
- 포인터로 구조체의 주소를 전달하여 함수에 사용.

유의사항 오답노트 주의할 것 기억할 것:
const char*를 받는 형식지정자를 %c 라고 했다가 오류남. 왜냐면 %c는 'a' 이런거 단일 문자 받음. 문자열 리터럴("HELLO" 이런거. H, E, L, L, O, \0(NULL)의 형태로 저장)을 출력하는 것이므로 %s (string) 으로 받아야 합니다...
닫는 중괄호 안 써서 갑자기 오류 52개 남. 인덴테이션 잘하고 괄호 누락 오타 주의하자...  특히 이중 for문 이런거....
*/