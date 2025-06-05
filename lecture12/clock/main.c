/* 20241341 석채희 시계 프로그램 */
// 아날로그 시계와 다지털 시계 + 스톱워치 기능 포함.
// 시계 조작법 : W - 스톱워치 모드로 변경 / T - 시계 모드로 변경
// S - 스톱위치 기록 시작 / E - 스톱위치 기록 중지



#pragma comment(lib, "Opengl32.lib") // OpenGL 라이브러리 링크 (MSVC 링커 지시문)

#include <GLFW/glfw3.h>           // GLFW: OpenGL 윈도우/입력 처리 라이브러리
#include <math.h>                 // 수학 함수(cos, sin 등)
#include <time.h>                 // 시간/날짜 함수 (time, clock)
#include <windows.h>              // Sleep 함수(윈도우 전용)
#include <stdio.h>                // 표준 입출력 (printf 등)
#include <string.h>               // 문자열 처리

#define M_PI 3.1415926535f        // 파이 상수 정의(일부 컴파일러에선 M_PI 미정의)



/* 기본 도우미 함수 */

//  원을 삼각형 팬(triangle‑fan)으로 채워서 그리기
//  x, y       : 원 중심 좌표
//  radius     : 반지름
//  segments   : 세분화(값이 클수록 더 부드러운 원)
void drawFilledCircle(float x, float y, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);     // (OpenGL 즉시 모드) 삼각형 팬 시작
    glVertex2f(x, y);             // 첫 번째 꼭짓점 → 원의 중심
    for (int i = 0; i <= segments; i++) {
        float angle = i * 2.0f * M_PI / segments; // 0~2π 각도 분할
        glVertex2f(x + cosf(angle) * radius,      // 호상의 점(x)
            y + sinf(angle) * radius);    //           (y)
    }
    glEnd();
}

//  끝이 둥근 바늘(시/분/초침) 그리기
//  angle_deg : 시계방향 각도(도)
//  length    : 바늘 길이 (NDC 비율)
//  width     : 바늘 두께
void drawRoundedHand(float angle_deg, float length, float width) {
    // 각도 → 라디안 변환 (deg × π/180)
    float angle_rad = angle_deg * M_PI / 180.0f;

    // 단위 방향 벡터(바늘 방향)
    float dx = cosf(angle_rad);
    float dy = sinf(angle_rad);

    // 바늘 폭에 따른 측변 벡터(수직 방향)
    float sx = dy * width / 2;  // 90º 회전 (dx,dy)→(-dy,dx)
    float sy = -dx * width / 2;

    // 바늘 끝점 좌표
    float tip_x = dx * length;
    float tip_y = dy * length;

    /* 1) 바늘 몸통(사각형) */
    glBegin(GL_QUADS);
    glVertex2f(-sx, -sy);                 // 사각형 4점: 시작 끝에서 폭만큼 오프셋
    glVertex2f(sx, sy);
    glVertex2f(tip_x + sx, tip_y + sy);
    glVertex2f(tip_x - sx, tip_y - sy);
    glEnd();

    /* 2) 둥근 끝(반원) */
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(tip_x, tip_y);             // 원의 중심점(바늘 끝)
    for (int i = 0; i <= 20; i++) {
        float theta = angle_rad + M_PI / 2 - i * M_PI / 20; // 180º 범위 분할
        glVertex2f(tip_x + cosf(theta) * width / 2,
            tip_y + sinf(theta) * width / 2);
    }
    glEnd();
}

//  12시 방향부터 60개의 점 형태 눈금 그리기
void drawTickMarks() {
    for (int i = 0; i < 60; i++) {
        float angle = i * 6.0f * M_PI / 180.0f; // 360º / 60 = 6º
        float cos_a = cosf(angle);
        float sin_a = sinf(angle);

        // 눈금 위치(반지름 0.8 지점)
        float centerX = cos_a * 0.8f;
        float centerY = sin_a * 0.8f;

        // 5분 눈금은 점을 크게(0.011), 나머지는 작게(0.004)
        float radius = (i % 5 == 0) ? 0.011f : 0.004f;

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(centerX, centerY);
        for (int j = 0; j <= 10; j++) {
            float theta = j * 2.0f * M_PI / 10; // 원 세분화
            float x = centerX + cosf(theta) * radius;
            float y = centerY + sinf(theta) * radius;
            glVertex2f(x, y);
        }
        glEnd();
    }
}



/*  육각형 세그먼트(디지털 숫자 LED 형태)  */
void drawHexSegment(float cx, float cy, float angle_deg, float length, float width) {
    float angle = angle_deg * M_PI / 180.0f; // 회전 각

    float triFraction = 0.1f;                // 양 끝 삼각 비율(10%)
    float L_rect = length * (1.0f - 2.0f * triFraction); // 중앙 사각형 길이

    // 육각형 정점(로컬 좌표): 좌→우 시계방향
    float vx[6], vy[6];
    vx[0] = -length / 2.0f;      vy[0] = 0.0f;
    vx[1] = -L_rect / 2.0f;      vy[1] = width / 2.0f;
    vx[2] = L_rect / 2.0f;      vy[2] = width / 2.0f;
    vx[3] = length / 2.0f;      vy[3] = 0.0f;
    vx[4] = L_rect / 2.0f;      vy[4] = -width / 2.0f;
    vx[5] = -L_rect / 2.0f;      vy[5] = -width / 2.0f;

    glBegin(GL_POLYGON);
    for (int i = 0; i < 6; i++) {
        // 회전 후 전역좌표 = 회전행렬(cx,cy)
        float rx = vx[i] * cosf(angle) - vy[i] * sinf(angle);
        float ry = vx[i] * sinf(angle) + vy[i] * cosf(angle);
        glVertex2f(cx + rx, cy + ry);
    }
    glEnd();
}

/*  한 자리 디지털 숫자(0~9) 그리기  */
void drawDigitSegment(float x, float y, float size, int digit) {
    // 각 세그먼트의 위치·회전 정보(7‑세그먼트 표준)
    struct { float dx, dy; float angle; } segments[7] = {
        { 0.0f,          size * 0.3f,  0.0f  }, // 0: 상단 가로
        { size * 0.20f,  size * 0.16f, 90.0f }, // 1: 우상단 세로
        { size * 0.20f, -size * 0.16f, 90.0f }, // 2: 우하단 세로
        { 0.0f,         -size * 0.3f,  0.0f  }, // 3: 하단 가로
        { -size * 0.20f,-size * 0.16f, 90.0f }, // 4: 좌하단 세로
        { -size * 0.20f, size * 0.16f, 90.0f }, // 5: 좌상단 세로
        { 0.0f,          0.0f,         0.0f  }  // 6: 중간 가로
    };

    // 7‑세그먼트 비트패턴(가로→세로→... 순서)
    static const unsigned char digitMap[10] = {
        0b1111110, // 0
        0b0110000, // 1
        0b1101101, // 2
        0b1111001, // 3
        0b0110011, // 4
        0b1011011, // 5
        0b1011111, // 6
        0b1110000, // 7
        0b1111111, // 8
        0b1111011  // 9
    };

    float segmentLength = size * 0.3f; // 길이 및 폭(상대값)
    float segmentWidth = size * 0.08f;

    // 1) 모든 세그먼트를 밝은 회색으로 기본 그리기 (꺼진 상태 표현)
    glColor3f(0.85f, 0.85f, 0.85f);
    for (int i = 0; i < 7; i++) {
        drawHexSegment(x + segments[i].dx, y + segments[i].dy,
            segments[i].angle, segmentLength, segmentWidth);
    }

    // 2) 현재 digit에 해당하는 세그먼트만 갈색(켜진 상태)으로 덮어쓰기
    glColor3f(0.6f, 0.4f, 0.2f);
    unsigned char pattern = digitMap[digit];
    for (int i = 0; i < 7; i++) {
        if (pattern & (1 << (6 - i))) {   // 비트 검사
            drawHexSegment(x + segments[i].dx, y + segments[i].dy,
                segments[i].angle, segmentLength, segmentWidth);
        }
    }
}

//  콜론( : ) 두 점
void drawColon(float x, float y, float radius) {
    drawFilledCircle(x, y + 0.06f, radius, 20); // 위 점
    drawFilledCircle(x, y - 0.06f, radius, 20); // 아래 점
}



/*  전역 상태  */
int g_mode = 0;                  // 0: 일반 시계, 1: 스톱워치
int stopwatch_running = 0;       // 스톱워치 동작 여부
clock_t stopwatch_start = 0;     // 시작 시각(clock 단위)
clock_t stopwatch_accumulated = 0; // 일시정지까지 누적 시간

// 키 입력 토글 감지용 이전 상태 저장
int prevW = 0, prevS = 0, prevT = 0, prevE = 0;

/*  스톱워치 시간(분:초.밀리초) 표시  */
void drawStopwatchClock(double swTime) {
    int minutes = (int)(swTime / 60);
    int seconds = ((int)swTime) % 60;
    int milliseconds = (int)((swTime - (int)swTime) * 1000);

    float startX = -0.46f; // 좌측 시작 위치
    float y = -0.32f; // Y 위치
    float size = 0.5f;   // 기본 크기

    //  분 & 초 (MM:SS)
    drawDigitSegment(startX, y, size, minutes / 10);
    drawDigitSegment(startX + 0.28f, y, size, minutes % 10);
    glColor3f(0.6f, 0.4f, 0.2f);
    drawColon(startX + 0.46f, y, size * 0.05f);
    drawDigitSegment(startX + 0.64f, y, size, seconds / 10);
    drawDigitSegment(startX + 0.92f, y, size, seconds % 10);

    //  밀리초 (위쪽 작은 글씨)
    float msSize = 0.3f * size;
    float msStartX = startX + 0.64f; // 초 자리 위쪽
    float msY = y + 0.25f;

    int d0 = (milliseconds / 100) % 10;
    int d1 = (milliseconds / 10) % 10;
    int d2 = milliseconds % 10;
    drawDigitSegment(msStartX, msY, msSize, d0);
    drawDigitSegment(msStartX + 0.5f * msSize, msY, msSize, d1);
    drawDigitSegment(msStartX + 1.0f * msSize, msY, msSize, d2);
}

/*  일반 디지털 시계(HH:MM)  */
void drawDigitalClock(int hour, int minute) {
    float startX = -0.46f;
    float y = -0.32f;
    float size = 0.5f;

    drawDigitSegment(startX, y, size, hour / 10);
    drawDigitSegment(startX + 0.28f, y, size, hour % 10);
    glColor3f(0.6f, 0.4f, 0.2f);
    drawColon(startX + 0.46f, y, size * 0.05f);
    drawDigitSegment(startX + 0.64f, y, size, minute / 10);
    drawDigitSegment(startX + 0.92f, y, size, minute % 10);
}



/*  main  */
int main(void) {
    /* GLFW 초기화 */
    if (!glfwInit())                // 실패 시 0 반환
        return -1;

    /* 창 생성 */
    GLFWwindow* window = glfwCreateWindow(550, 550, "Clock", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // OpenGL 컨텍스트 활성화

    /* 투영/뷰포트 세팅 */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);  // 정규직교투영 (NDC 직접 매핑)
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 배경색(흰)

    /* 메인 루프(약 60 FPS) */
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        /* 시계 배경 원 */
        glColor3f(1.0f, 0.8f, 0.3f);   // 외곽(노란)
        drawFilledCircle(0.0f, 0.0f, 0.95f, 100);
        glColor3f(1.0f, 1.0f, 0.9f);   // 안쪽(흰)
        drawFilledCircle(0.0f, 0.0f, 0.85f, 100);

        /* 현재 시각 가져오기 */
        time_t now = time(NULL);
        struct tm* t = localtime(&now);

        /* 키 입력 처리 */
        int curW = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS); // W: 스톱워치 모드 진입
        int curS = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS); // S: 스타트(재개)
        int curE = (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS); // E: 스톱(일시정지)
        int curT = (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS); // T: 일반 시계 복귀

        if (curW && !prevW) {           // W 눌림
            g_mode = 1;                 // 모드 전환
            stopwatch_running = 0;      // 스톱워치 초기화
            stopwatch_accumulated = 0;
        }
        if (g_mode == 1 && curS && !prevS) {
            if (!stopwatch_running) {
                stopwatch_running = 1;
                stopwatch_start = clock(); // 현재 프로세스 시간 저장
            }
        }
        if (g_mode == 1 && curE && !prevE) { // E: 멈춤
            if (stopwatch_running) {
                stopwatch_accumulated += clock() - stopwatch_start; // 누적
                stopwatch_running = 0;
            }
        }
        if (g_mode == 1 && curT && !prevT) { // T: 일반 시계 복귀
            g_mode = 0;
        }
        // 이번 프레임 입력 상태 저장 (토글 검사용)
        prevW = curW; prevS = curS; prevT = curT; prevE = curE;
        /* 키 입력 처리 끝 */

        /* 디지털/스톱워치 표시 */
        if (g_mode == 0) {
            drawDigitalClock(t->tm_hour, t->tm_min);    // HH:MM
        }
        else {
            double swTime = (double)stopwatch_accumulated / CLOCKS_PER_SEC;
            if (stopwatch_running) {
                swTime += (double)(clock() - stopwatch_start) / CLOCKS_PER_SEC;
            }
            drawStopwatchClock(swTime);
        }

        /* 왼쪽 위 초침 전용 소형 시계 */
        {
            float cx = -0.4f, cy = 0.25f, radius = 0.22f;

            // 외곽(검정)
            glColor3f(0.0f, 0.0f, 0.0f);
            drawFilledCircle(cx, cy, radius * 1.05f, 45);

            // 배경(갈색)
            glColor3f(0.25f, 0.15f, 0.1f);
            drawFilledCircle(cx, cy, radius, 45);

            // 60초 눈금(주/소)
            for (int i = 0; i < 60; i++) {
                float angle = i * 6.0f * M_PI / 180.0f;
                float innerFactor = (i % 5 == 0) ? 0.85f : 0.90f;
                float x1 = cx + cosf(angle) * radius * innerFactor;
                float y1 = cy + sinf(angle) * radius * innerFactor;
                float x2 = cx + cosf(angle) * radius * 0.95f;
                float y2 = cy + sinf(angle) * radius * 0.95f;

                glColor3f(1.0f, 0.8f, 0.0f);
                glLineWidth(1.0f);
                glBegin(GL_LINES);
                glVertex2f(x1, y1);
                glVertex2f(x2, y2);
                glEnd();
            }

            // 초침(빨강)
            float sec_angle = t->tm_sec * 6.0f;                 // 0~59 → 0~354º
            float angle_rad = (360.0f - sec_angle + 90.0f) * M_PI / 180.0f; // 시계 좌표계 보정
            float handLength = radius * 0.85f;
            float x_tip = cx + cosf(angle_rad) * handLength;
            float y_tip = cy + sinf(angle_rad) * handLength;

            glColor3f(1.0f, 0.0f, 0.0f);
            glLineWidth(1.5f);
            glBegin(GL_LINES);
            glVertex2f(cx, cy);
            glVertex2f(x_tip, y_tip);
            glEnd();

            // 중심 원
            glColor3f(0.0f, 0.0f, 0.0f);
            drawFilledCircle(cx, cy, radius * 0.05f, 20);
        }

        /* 메인 아날로그 시계 */
        {
            // 현재 시·분·초(12시간제)
            int hour = t->tm_hour % 12;
            int minute = t->tm_min;
            int second = t->tm_sec;

            // 각도 계산
            float hour_angle = (hour + minute / 60.0f) * 30.0f; // 360/12
            float min_angle = (minute + second / 60.0f) * 6.0f; // 360/60
            float sec_angle = second * 6.0f;

            // 눈금점(바깥) & 바늘
            glColor3f(0.2f, 0.15f, 0.1f);
            drawTickMarks();

            // drawRoundedHand는 0º가 +X, 반시계(+)
            drawRoundedHand(360.0f - hour_angle + 90.0f, 0.3f, 0.05f); // 시침
            drawRoundedHand(360.0f - min_angle + 90.0f, 0.5f, 0.03f); // 분침
            drawRoundedHand(360.0f - sec_angle + 90.0f, 0.76f, 0.012f); // 초침

            drawFilledCircle(0.0f, 0.0f, 0.04f, 20); // 중심 고정핀
        }

        /* 버퍼 스왑 & 이벤트 */
        glfwSwapBuffers(window);   // 더블 버퍼 교체
        glfwPollEvents();          // 입력/창 이벤트 처리
        Sleep(16);                // 16ms ≒ 60FPS (간단한 프레임 제한)
    }

    /* 프로그램 종료 전 GLFW 정리 */
    glfwTerminate();
    return 0;
}
