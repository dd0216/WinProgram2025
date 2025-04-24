#include <stdio.h>
#include <Windows.h>

// �ܼ� Ŀ�� �̵� �Լ�
void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

// ANSI ��� ���� ���� (0~7)
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

// ���� �۾� ǥ������ �׸��� �Լ�
void DrawBG(int width, int height) {
    for (int i = 0; i < height; i++) {
        if (i == 0) {
            // ��� ����
            printf("\n");
        }
        else if (i == height - 1) {
            // �۾� ǥ���� (�ϴ� �� ��, ȸ�� ���)
            printf("  "); // �� ����
            for (int j = 0; j < width - 4; j++) {
                printf("\033[100m \033[0m"); // ȸ�� ���
            }
            printf("  \n"); // �� ����
        }
        else {
            // �Ϲ� ��� �� (�Ķ���)
            printf("  "); // �� ����
            for (int j = 0; j < width - 4; j++) {
                printf("\033[44m \033[0m"); // �Ķ� ���
            }
            printf("  \n"); // �� ����
        }
    }
}

// �ܼ� ������ �׸��� �Լ�
void drawConsoleWindow(int startX, int startY, int width, int height, const char* title, int color) {
    const char* bg = bgColors[color % 8];

    // ������ ���� ���� �׸���
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            gotoxy(startX + x, startY + y);
            printf("%s \033[0m", bg); // �⺻ ���
        }
    }

    // ������ �׵θ� �׸��� (���)
    for (int x = 0; x < width; x++) {
        // ��� �׵θ�
        gotoxy(startX + x, startY);
        printf("\033[44m-\033[0m");
        // �ϴ� �׵θ�
        gotoxy(startX + x, startY + height - 1);
        printf("\033[44m-\033[0m");
    }
    for (int y = 1; y < height - 1; y++) {
        // ���� �׵θ�
        gotoxy(startX, startY + y);
        printf("\033[44m|\033[0m");
        // ���� �׵θ�
        gotoxy(startX + width - 1, startY + y);
        printf("\033[44m|\033[0m");
    }

    // Ÿ��Ʋ ǥ�� (�� ��濡 ���� ����)
    gotoxy(startX + 2, startY);
    printf("\033[30m\033[47m%s\033[0m", title);

    // X ��ư (�� ������ ���� 3ĭ, ���� ��濡 ��� �ؽ�Ʈ)
    gotoxy(startX + width - 4, startY);
    printf("\033[41m\033[97mX\033[0m");
}

int main() {
    int width = 80;
    int height = 25;

    system("cls");
    DrawBG(width, height); // ��� + �۾� ǥ���� �׸���

    // ������ 3�� �׸���
    drawConsoleWindow(10, 3, 25, 7, "���� ������ 1", 3);
    drawConsoleWindow(20, 10, 25, 7, "���� ������ 2", 1);
    drawConsoleWindow(35, 5, 25, 7, "���� ������ 3", 2);

    gotoxy(0, 25);
    return 0;
}
