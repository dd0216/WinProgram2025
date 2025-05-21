#include <GLFW/glfw3.h>
#include <math.h>
#pragma comment(lib, "Opengl32.lib")

#define PI 3.1415926535f

typedef struct
{
    float x, y;
} Vec2;

typedef struct
{
    Vec2 position;
    float rotation;    // ¶óµð¾È
    Vec2 scale;
} Transform;

typedef struct
{
    Transform transform;
} Triangle;

void draw_triangle(Triangle* tri)
{
    glPushMatrix();

    glTranslatef(tri->transform.position.x, tri->transform.position.y, 0.0f);
    glRotatef(tri->transform.rotation * (180.0f / PI), 0.0f, 0.0f, 1.0f);
    glScalef(tri->transform.scale.x, tri->transform.scale.y, 1.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    glPopMatrix();
}

typedef struct
{
    Transform transform;
} Square;

void draw_square(Square* sq)
{
    glPushMatrix();

    glTranslatef(sq->transform.position.x, sq->transform.position.y, 0.0f);
    glRotatef(sq->transform.rotation * (180.0f / PI), 0.0f, 0.0f, 1.0f);
    glScalef(sq->transform.scale.x, sq->transform.scale.y, 1.0f);

    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(-0.5f, -0.5f);
    glEnd();

    glPopMatrix();
}

typedef struct
{
    Transform transform;
    int segments;
} Circle;

void draw_circle(Circle* c)
{
    glPushMatrix();

    glTranslatef(c->transform.position.x, c->transform.position.y, 0.0f);  //트랜스폼자료구조안에 포지션자료구조안에 x값
    glRotatef(c->transform.rotation * (180.0f / PI), 0.0f, 0.0f, 1.0f);
    glScalef(c->transform.scale.x, c->transform.scale.y, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.0f, 0.0f);

    for (int i = 0; i <= c->segments; ++i)
    {
        float angle = 2.0f * PI * i / c->segments;
        glVertex2f(cosf(angle) * 0.5f, sinf(angle) * 0.5f);
    }

    glEnd();

    glPopMatrix();
}

int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL C Demo", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(-1, 1, -1, 1, -1, 1); // 2D

    Triangle tri = { {{0, 0}, 0, {1, 1}} };
    Square sq = { {{-0.5f, -0.5f}, 0, {1, 1}} };
    Circle cir = { {{0.5f, 0.5f}, 0, {1, 1}}, 32 };

    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();

        // ¾Ö´Ï¸ÞÀÌ¼Ç ¿¹½Ã
        tri.transform.position.x = sinf(time);
        sq.transform.rotation = time;
        cir.transform.scale.x = 1.0f + 0.5f * sinf(time);

        glClear(GL_COLOR_BUFFER_BIT);

        draw_triangle(&tri);
        draw_square(&sq);
        draw_circle(&cir);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}