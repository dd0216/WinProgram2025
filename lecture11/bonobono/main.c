#pragma comment(lib, "Opengl32.lib")  // 별도의 프로젝트 설정 없이 라이브러리를 링크할 수 있는 문장.
#define M_PI 3.1415926535f

#include <GLFW/glfw3.h>
#include <math.h>

void drawEllipse(float cx, float cy, float rx, float ry, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float theta = i * 2.0f * M_PI / segments;
        glVertex2f(cx + cos(theta) * rx, cy + sin(theta) * ry);
    }
    glEnd();
}

void drawEllipseLine(float cx, float cy, float rx, float ry, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * M_PI * (float)i / segments;
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawLine(float x1, float y1, float length, float angle) {
    float x2 = x1 + length * cos(angle * M_PI / 180.0f);
    float y2 = y1 + length * sin(angle * M_PI / 180.0f);

    glBegin(GL_LINES); // 선 그리기 시작
    glVertex2f(x1, y1); // 시작점
    glVertex2f(x2, y2); // 끝점
    glEnd(); // 선 그리기 종료
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(537, 445, "Bonobono Drawing", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 흰색 배경 설정
    glLineWidth(2.4f); // 모든 선의 기본 두께를 2.4f로 설정 (만약 특정 함수에서만 다른 두께를 설정하고 싶다면, 해당 함수 내부에서 glLineWidth()를 호출하면 됨.)

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // 파란색 얼굴 (RGB: 0, 112, 192)
        glColor3f(0.2f, 0.6f, 1.0f);
        drawEllipse(-0.01f, 0.0f, 0.8f, 0.89f, 500); // (타원: 중심x, 중심y, 반지름x, 반지름y, 세그먼트)

        // 검은색 얼굴선
        glColor3f(0.0f, 0.0f, 0.0f);
        drawEllipseLine(-0.01f, 0.0f, 0.8f, 0.89f, 500);

        // 검은색 눈동자
        glColor3f(0.0f, 0.0f, 0.0f);
        drawEllipse(-0.67f, 0.2f, 0.06f, 0.07f, 50);
        drawEllipse(0.59f, 0.18f, 0.061f, 0.072f, 50);

        // 흰색 주둥이
        glColor3f(1.0f, 1.0f, 1.0f);
        drawEllipse(-0.14f, -0.28f, 0.17f, 0.17f, 70);
        drawEllipse(0.14f, -0.28f, 0.17f, 0.17f, 70);
        
        // 검은색 코
        glColor3f(0.0f, 0.0f, 0.0f);
        drawEllipse(0.0f, -0.1f, 0.12f, 0.12f, 50);

        // 검은색 왼쪽 수염
        drawLine(-0.20f, -0.2f, 0.24f, 160.0f);  // (선: 시작점x좌표, 시작점y좌표, 길이, 각도)
        drawLine(-0.21f, -0.3f, 0.24f, 180.0f);
        drawLine(-0.19f, -0.36f, 0.26f, 200.0f);

        // 검은색 오른쪽 수염
        drawLine(0.18f, -0.2f, 0.25f, 20.0f);
        drawLine(0.18f, -0.29f, 0.25f, 0.0f);
        drawLine(0.17f, -0.375f, 0.25f, -16.0f);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
