#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define PI 3.1415926535f

void draw_square()
{
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);             // 색상: 초록색
    glVertex2f(-0.3f, 0.3f);                  // 첫 번째 꼭짓점: 왼쪽 위
    glVertex2f(0.3f, 0.3f);                   // 두 번째 꼭짓점: 오른쪽 위
    glVertex2f(0.3f, -0.3f);                  // 세 번째 꼭짓점: 오른쪽 아래
    glVertex2f(-0.3f, -0.3f);                 // 네 번째 꼭짓점: 왼쪽 아래
    glEnd();
}

void draw_mouse()
{
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);             // 색상: 검정색
    glVertex2f(-0.1f, -0.1f);                  // 첫 번째 꼭짓점: 왼쪽 위
    glVertex2f(0.1f, -0.1f);                   // 두 번째 꼭짓점: 오른쪽 위
    glVertex2f(0.1f, -0.2f);                  // 세 번째 꼭짓점: 오른쪽 아래
    glVertex2f(-0.1f, -0.2f);                 // 네 번째 꼭짓점: 왼쪽 아래
    glEnd();
}

void draw_lefteye()
{
    glBegin(GL_QUADS); // -0.2f, 0.15f, 0.03f, 40
    glColor3f(0.0f, 0.0f, 0.0f);             // 색상: 검정색
    glVertex2f(-0.2f, 0.15f);                  // 첫 번째 꼭짓점: 왼쪽 위
    glVertex2f(-0.1f, 0.15f);                   // 두 번째 꼭짓점: 오른쪽 위
    glVertex2f(-0.1f, 0.05f);                  // 세 번째 꼭짓점: 오른쪽 아래
    glVertex2f(-0.2f, 0.05f);                 // 네 번째 꼭짓점: 왼쪽 아래
    glEnd();
}
void draw_righteye()
{
    glBegin(GL_QUADS); // -0.2f, 0.15f, 0.03f, 40
    glColor3f(0.0f, 0.0f, 0.0f);             // 색상: 검정색
    glVertex2f(0.2f, 0.15f);                  // 첫 번째 꼭짓점: 왼쪽 위
    glVertex2f(0.1f, 0.15f);                   // 두 번째 꼭짓점: 오른쪽 위
    glVertex2f(0.1f, 0.05f);                  // 세 번째 꼭짓점: 오른쪽 아래
    glVertex2f(0.2f, 0.05f);                 // 네 번째 꼭짓점: 왼쪽 아래
    glEnd();
}

//////


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

        draw_square();

        draw_mouse();

        draw_lefteye();

        draw_righteye();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
