#include <windows.h>
#include <stdio.h>

int main() {
    char letter = 'O';  // ���ĺ� 'O' ����
    POINT mousePos = { 0, 0 };     // ���콺 ��ġ (�ʱ�ȭ
    int isDragging = 0;  // �巡�� ���� (0: �巡�� �� �ƴ�, 1: �巡�� ��)
    int letterX = 10;    // ���ĺ� 'O'�� �ʱ� X ��ǥ
    int letterY = 5;     // ���ĺ� 'O'�� �ʱ� Y ��ǥ
    int dragRange = 2;   // �巡�� ������ ������ ��� ���� �߰���. (�����¿� 2 �ؽ�Ʈ �� �̳�)

    while (1) {
        // ȭ�� ����
        system("cls");  // ȭ�� �ʱ�ȭ
        printf("���ĺ� '%c'�� ���콺�� �巡���ϼ���.\n", letter);
        printf("���� ���ĺ� '%c'�� ��ġ: (%d, %d)\n", letter, letterX, letterY);

        // ���ĺ� O ���
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { letterX, letterY });
        printf("%c", letter);

        // ���� ���콺 ���� ��������
        if (GetCursorPos(&mousePos)) {
            // ���콺 ���� ��ư Ŭ�� ���� Ȯ��
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                // ���� ��ó�� ���� �� �巡�� ����
                int mouseX = mousePos.x / 9;
                int mouseY = mousePos.y / 19 - 2;  // -2�� Ÿ��Ʋ �ٸ� ����� ��ġ ����

                if (!isDragging &&
                    mouseX >= (letterX - dragRange) && mouseX <= (letterX + dragRange) &&
                    mouseY >= (letterY - dragRange) && mouseY <= (letterY + dragRange)) {
                    isDragging = 1; // �巡�� ����
                }
            }
            else {
                isDragging = 0; // �巡�� ����
            }

            // �巡�� ���� �� ���� ��ġ ������Ʈ
            if (isDragging) {
                letterX = mousePos.x / 9;
                letterY = mousePos.y / 19 - 2;  // -2�� Ÿ��Ʋ �ٸ� ����� ��ġ ����
            }
        }

        // ���� ����: ESC Ű�� ������ ���α׷� ����
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            printf("\n���α׷� ����\n");
            break;
        }

        // ��� ��� (CPU ��� ����ȭ)
        Sleep(10);
    }

    return 0;
}

