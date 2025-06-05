#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define PI 3.1415926535f

// 얼굴 그리기 함수 구현
void drawCircle(float cx, float cy, float r, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float angle = i * 2.0f * PI / segments;
        glVertex2f(cx + cosf(angle) * r, cy + sinf(angle) * r);
    }
    glEnd();
}

// 입 그리기 함수 구현
void drawSemiCircle(float cx, float cy, float r, int segments) {
    glBegin(GL_TRIANGLE_FAN); // 삼각형 팬(FAN) 방식으로 반원을 그림
    glVertex2f(cx, cy); // 중심점 지정

    // 반원의 시작 각도는 PI(180도), 끝 각도는 2PI(360도)
    for (int i = 0; i <= segments; i++) {
        float angle = PI + (PI * i / segments); // 각도 계산: 180도~360도 범위
        float x = cx + cosf(angle) * r * 2; // X 좌표 계산 (cos 함수 이용) + 가로 2배 스케일 늘리기
        float y = cy + sinf(angle) * r; // Y 좌표 계산 (sin 함수 이용)
        glVertex2f(x, y); // 계산된 점을 추가
    }

    glEnd(); // 삼각형 팬 종료
}

void drawline()
{
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);             // 색상: 
    glVertex2f(0.5f, 0.02f);                  // 첫 번째 꼭짓점: 왼쪽 위
    glVertex2f(0.1f, 0.02f);                   // 두 번째 꼭짓점: 오른쪽 위
    glEnd();
}
void drawline2()
{
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);             // 색상:
    glVertex2f(-0.1f, 0.02f);                  // 첫 번째 꼭짓점: 왼쪽 위
    glVertex2f(-0.05f, 0.02f);                   // 두 번째 꼭짓점: 오른쪽 위
    glEnd();
}

int main(void) {
    if (!glfwInit()) {
        printf("GLFW 초기화 실패!\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 800, "20241341_seokchaehee", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glLineWidth(5.0f); // 선 두께를 5px로 설정

    while (!glfwWindowShouldClose(window)) {  // 렌더링 루프 (창 유지)
        glClear(GL_COLOR_BUFFER_BIT);

        // 얼굴 그리기 호출
        glColor3f(1.0f, 0.82f, 0.0f);
        drawCircle(0.0f, 0.0f, 0.15f, 200);
        // (float cx, float cy, float r, int segments)

        // 입 그리기 호출
        glColor3f(1.0f, 0.0f, 0.0f);
        drawSemiCircle(0.0f, -0.05f, 0.03f, 50); // 중앙 아래 위치에 반원 그리기
        // (float cx, float cy, float r, int segments)

        //눈그리기
        glColor3f(0.0f, 0.0f, 0.0f);
        drawline(0.02f, 0.09f, 0.0002f);
        // (float x, float y, float size)

        drawline2();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}