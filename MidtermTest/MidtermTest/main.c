#include <stdio.h>

// PassOrFail 함수 정의
int PassOrFail(int score) {
    if (score >= 50) {
        return 1;
    }
    else {
        return 0;
    }
}

// main 함수
int main() {
    int Score = 50; // 본인의 예상 점수를 여기에 입력
    int result = PassOrFail(Score);

    if (result == 1) {
        printf("재시험 없습니다!\n");
    }
    else {
        printf("우리는 망했다… 재시험이다…\n");
    }

    return 0;
}