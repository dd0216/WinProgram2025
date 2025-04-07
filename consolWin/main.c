#include <Windows.h>
#include <stdio.h>

// �ܼ� ȭ�鿡�� Ŀ���� (x, y) ��ġ�� �̵���Ű�� �Լ�
void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, Cur);
}

// ������ ���� ����ü ����
typedef struct {
	int startX;  // ������ x ���� ��ġ
	int startY; // ������ y ���� ��ġ
	const char* windowName;  //������ �̸�
	const char* windowColor;  //������ ���� 
} windowInfo;

// ������ ���� ����
#define numWindows 3

// ����ü �迭 ����
windowInfo windows[numWindows] = {
	{10, 3, "���� ������ 1", "\033[43m"},  //�����
	{15, 5, "���� ������ 2",  "\033[41m"},  // ������
	{40, 7, "���� ������ 3",  "\033[44m"},  // �Ķ���
};

// ������ �׸��� �Լ�
int drawWindow(windowInfo* win) {
	int width = 20;
	int height = 7;

	// �� ȭ�� �׸���
	for (int x = 1; x < width; x++) {
		for (int y = 1; y < height; y++) {
			gotoxy(win->startX + x, win->startY + y);
			printf("\033[47m ");
		}

	}

	// ������ �̸� ����
	gotoxy(win->startX + 1, win->startY + 1);
	printf("\033[30m\033[47m%s", win->windowName);

    // ���� �׵θ� �� �׸���
	for (int x = 0; x < width; x++) {
		gotoxy(win->startX + x, win->startY);  // ����
		printf("%s ", win->windowColor);

		gotoxy(win->startX + x, win->startY + 2);  // �߰���
		printf("%s ", win->windowColor);

		gotoxy(win->startX + x, win->startY + height - 1);  // �Ʒ���
		printf("%s ", win->windowColor);
	}
		
    // ���� �׵θ� �� �׸���
	for (int y = 1; y < height - 1; y++) {
		gotoxy(win->startX, win->startY + y);  // ���� ���μ�
		printf("%s ", win->windowColor);

		gotoxy(win->startX + width - 1, win->startY + y);  // ������ ���μ�
		printf("%s \033[0m", win->windowColor);
	}
    return 0;
}

//��� �׸��� �Լ�
int drawBackground() {
	for (int i = 0; i < 29; i++) {
		puts("\033[32m\033[42m���ȭ����ȭ����ȭ����ȭ����ȭ����ȭ����ȭ����ȭ����ȭ����ȭ����ȭ����ȭ����ȭ����ȭ����ȭ��\033[0m");
	}
	return 0;
}

int main() {
	drawBackground();  // ��� ���� �Լ� ȣ��

	for (int i = 0; i < numWindows; ++i) {  // ������ ���� �Լ� ȣ��
		drawWindow(&windows[i]);
	}

	gotoxy(0, 29);
	return 0;
}