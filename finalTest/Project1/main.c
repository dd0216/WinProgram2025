#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define PI 3.1415926535f

void draw_square()
{
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);             // ����: �ʷϻ�
    glVertex2f(-0.3f, 0.3f);                  // ù ��° ������: ���� ��
    glVertex2f(0.3f, 0.3f);                   // �� ��° ������: ������ ��
    glVertex2f(0.3f, -0.3f);                  // �� ��° ������: ������ �Ʒ�
    glVertex2f(-0.3f, -0.3f);                 // �� ��° ������: ���� �Ʒ�
    glEnd();
}

void draw_mouse()
{
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);             // ����: ������
    glVertex2f(-0.1f, -0.1f);                  // ù ��° ������: ���� ��
    glVertex2f(0.1f, -0.1f);                   // �� ��° ������: ������ ��
    glVertex2f(0.1f, -0.2f);                  // �� ��° ������: ������ �Ʒ�
    glVertex2f(-0.1f, -0.2f);                 // �� ��° ������: ���� �Ʒ�
    glEnd();
}

void draw_lefteye()
{
    glBegin(GL_QUADS); // -0.2f, 0.15f, 0.03f, 40
    glColor3f(0.0f, 0.0f, 0.0f);             // ����: ������
    glVertex2f(-0.2f, 0.15f);                  // ù ��° ������: ���� ��
    glVertex2f(-0.1f, 0.15f);                   // �� ��° ������: ������ ��
    glVertex2f(-0.1f, 0.05f);                  // �� ��° ������: ������ �Ʒ�
    glVertex2f(-0.2f, 0.05f);                 // �� ��° ������: ���� �Ʒ�
    glEnd();
}
void draw_righteye()
{
    glBegin(GL_QUADS); // -0.2f, 0.15f, 0.03f, 40
    glColor3f(0.0f, 0.0f, 0.0f);             // ����: ������
    glVertex2f(0.2f, 0.15f);                  // ù ��° ������: ���� ��
    glVertex2f(0.1f, 0.15f);                   // �� ��° ������: ������ ��
    glVertex2f(0.1f, 0.05f);                  // �� ��° ������: ������ �Ʒ�
    glVertex2f(0.2f, 0.05f);                 // �� ��° ������: ���� �Ʒ�
    glEnd();
}

//////


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
