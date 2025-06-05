#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define PI 3.1415926535f

// �� �׸��� �Լ� ����
void drawCircle(float cx, float cy, float r, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float angle = i * 2.0f * PI / segments;
        glVertex2f(cx + cosf(angle) * r, cy + sinf(angle) * r);
    }
    glEnd();
}

// �� �׸��� �Լ� ����
void drawSemiCircle(float cx, float cy, float r, int segments) {
    glBegin(GL_TRIANGLE_FAN); // �ﰢ�� ��(FAN) ������� �ݿ��� �׸�
    glVertex2f(cx, cy); // �߽��� ����

    // �ݿ��� ���� ������ PI(180��), �� ������ 2PI(360��)
    for (int i = 0; i <= segments; i++) {
        float angle = PI + (PI * i / segments); // ���� ���: 180��~360�� ����
        float x = cx + cosf(angle) * r * 2; // X ��ǥ ��� (cos �Լ� �̿�) + ���� 2�� ������ �ø���
        float y = cy + sinf(angle) * r; // Y ��ǥ ��� (sin �Լ� �̿�)
        glVertex2f(x, y); // ���� ���� �߰�
    }

    glEnd(); // �ﰢ�� �� ����
}

void drawline()
{
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);             // ����: 
    glVertex2f(0.5f, 0.02f);                  // ù ��° ������: ���� ��
    glVertex2f(0.1f, 0.02f);                   // �� ��° ������: ������ ��
    glEnd();
}
void drawline2()
{
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);             // ����:
    glVertex2f(-0.1f, 0.02f);                  // ù ��° ������: ���� ��
    glVertex2f(-0.05f, 0.02f);                   // �� ��° ������: ������ ��
    glEnd();
}

int main(void) {
    if (!glfwInit()) {
        printf("GLFW �ʱ�ȭ ����!\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 800, "20241341_seokchaehee", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glLineWidth(5.0f); // �� �β��� 5px�� ����

    while (!glfwWindowShouldClose(window)) {  // ������ ���� (â ����)
        glClear(GL_COLOR_BUFFER_BIT);

        // �� �׸��� ȣ��
        glColor3f(1.0f, 0.82f, 0.0f);
        drawCircle(0.0f, 0.0f, 0.15f, 200);
        // (float cx, float cy, float r, int segments)

        // �� �׸��� ȣ��
        glColor3f(1.0f, 0.0f, 0.0f);
        drawSemiCircle(0.0f, -0.05f, 0.03f, 50); // �߾� �Ʒ� ��ġ�� �ݿ� �׸���
        // (float cx, float cy, float r, int segments)

        //���׸���
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