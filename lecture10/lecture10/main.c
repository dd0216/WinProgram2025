// opengl 점 선 면 삼각형 원 그리기 (우리가 지금 하는 건 오픈GL 1.0)
/* 프로젝트 이름 우클릭한 후 Nuget 패키지 관리 (패키지 매니저)에서 GLFW를 설치할 것!*/



#pragma comment(lib, "Opengl32.lib")  // 이 문장 없으니까 오류낫었음..... 이 라이브러리 쓰는거구나 링커 해주는 문장.!
#include <GLFW/glfw3.h>  // glfw 폴더 안에 있는 glfw3 쓴다는 소리인교
#include <math.h>



#ifndef M_PI  // 만약 M_PI가 정의되지 않았다면 정의해라라는 전처리기 지시문 (중복정의 방지! 이미 정의된 게 있으면 새로 정의 되지않음.)
#define M_PI 3.14159265358979323846  // 컴파일러 문젠지 왜인지 안되서...  M_PI가 없다면서 안되서 직접 정의했음...
#endif  // ifndef를 끝내는 문장 적어주기.



void draw_triangle() {
    glBegin(GL_TRIANGLES);  // 그림을 그리기 시작할것임 (삼각형을!) 하드웨어 대기해라!! - 세상을 이루는 점선면을 그려보자. (삼각형은 면의 최소단위)
    glColor3f(1.0f, 0.0f, 0.0f);  // 빨간색 점 색깔 지정 : 컬러는 하나씩 찍는 점의 색깔을 정해주고 그 점을 찎어라! 라는 코드 (R G B, 각각 1이 최고, 0이 최저치)
    glVertex2f(-0.5f, -0.5f);  // 위에 말한 점을 (-0.5, -0.5) 위치에다가 찍어라
    glColor3f(0.0f, 1.0f, 0.0f);  // 초록색 점 정의
    glVertex2f(0.5f, -0.5f);  //(0.5, -0.5)에 찍어라
    glColor3f(0.0f, 0.0f, 1.0f);  // 파란색 점
    glVertex2f(0.0f, 0.5f);  // 찍어라 이 위치에
    glEnd();  // 위 점말고는 더 이상 그릴게 없다. (=하드웨어한테 이제 요것까찌만 그려! 끝이야! 더 이상 받아들일 점이 더 없으니 이제 요대로만 그리시면 돼요 하드웨어씨.)
}



void drawSquare() {
    glBegin(GL_TRIANGLES);  // 삼각형을 이용해 사각형 그리기 시작
 
    // 첫 번째 삼각형
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.5f, 0.5f);  // 왼쪽 위
    glVertex2f(-0.5f, -0.5f); // 왼쪽 아래
    glVertex2f(0.5f, 0.5f);   // 오른쪽 위

    // 두 번째 삼각형
    glVertex2f(0.5f, 0.5f);   // 오른쪽 위
    glVertex2f(-0.5f, -0.5f); // 왼쪽 아래
    glVertex2f(0.5f, -0.5f);  // 오른쪽 아래

    glEnd();  // 그리기 종료
}



/*
 glVertex2f 점 찍기 위치 (좌표 중심을 기준으로 함!)

X축 (왼쪽 ↔ 오른쪽)
-1 왼쪽 끝
0 중앙
1 오른쪽 끝

Y축 (위쪽 ↔ 아래쪽)
-1 아래쪽 끝
0 중앙
1 위쪽 끝

*/



void drawRainbowCircle(float cx, float cy, float r, int num_segments) {  // 원 그리기 함수 (cx, cy(중심 위치)와 r(반지름), 그리고 num_segments(원의 부드러움 정도를 입력받아..) 
    glBegin(GL_TRIANGLE_FAN);  // 삼각형 부채꼴(Triangle Fan) 방식으로 원을 그리기 시작

    // 중심점 (흰색)
    glColor3f(1.0f, 1.0f, 1.0f);  // 중심점을 흰색으로 설정하고 (RGB 값: 1.0, 1.0, 1.0)
    glVertex2f(cx, cy);  // 중심점 좌표(cx, cy) 지정해서 찍음.

    // 원을 num_segments 개의 작은 삼각형으로 나누어 그리기
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * M_PI * i / num_segments;  // 각도를 계산 (한 바퀴를 num_segments로 나눔) - 원을 작은 조각으로 나누고, 각 조각이 몇 도(각도)인지 계산.

        float x = r * cos(theta);  // 원의 x 좌표 계산 (cos 함수 활용)
        float y = r * sin(theta);  // 원의 y 좌표 계산 (sin 함수 활용)

        // 색상을 무지개처럼 변경 (Red -> Yellow -> Green -> Blue -> Purple)
        glColor3f((1.0f + cos(theta)) / 2.0f, (1.0f + sin(theta)) / 2.0f, (1.0f - cos(theta)) / 2.0f);  // 빨강(R): cos(theta) 값을 이용해 변동, 초록(G): sin(theta) 값을 이용해 변동, 파랑(B): cos(theta) 값을 반대로 변동

        glVertex2f(cx + x, cy + y);  // 계산된 위치에 점(정점) 추가
    }

    glEnd();  // 원 그리기 종료
}




int main() {
    if (!glfwInit()) return -1;  //GLFW인잇! GLFW를 초기화 시키겟다 - 메모리에 GLFW 관련된 내용이 다 올라간다는 문장. 실패 시 종료해버리고, 성공 시 GLFW가 잘 로드 된 것.

    GLFWwindow* window = glfwCreateWindow(500, 500, "GLFW: Triangle", NULL, NULL); // 윈도우를 (가로,세로,"창이름",모니터,컨텍스트쉐어)으로 만들어라. - 메모리를 생성하면 없애줘야한다!!!! 중요!!! 메모리 문제(컴파일 에러에선 알수없어 그냥 디버그모드일땐 잘돌아가다가 일반앱으로 됫을때 메모리 누수로 디져버리는경우발생...)
    if (!window) {
        glfwTerminate(); //터미네이트.. GLFW 닫고 지워줘야 한다.
        return -1;
    }

    glfwMakeContextCurrent(window);  // 컨텍스트(문맥)이 생겻다 (이 컨텍스트를 이윈도우의 최신화면으로 업데이트할거다) 이 윈도우의 GPU의 사용권을 내가 가져오겟다

    while (!glfwWindowShouldClose(window)) {  // 굉장히 또 조흔 함수 (얘는 창의 종료 여부를 확인하는 함수. true(1) 또는 false(0)를 반환 -> false 반환 시 창이 닫히지 않았다는 것이므로 와일루프 속으로 드간다), 이 와일문은 루프가 계속 실행되면서 화면을 새로 그리고, 사용자 입력 받고를 창이 닫힐 때까지 반복하는 구조.
        glClear(GL_COLOR_BUFFER_BIT);  // 쓰레기값(이전 프레임의 잔상)으로 가득 차 있으므로 단색으로 클리어를 하는 화면 초기화 (색상 버퍼 지워라)

        drawRainbowCircle(0.0f, 0.0f, 0.5f, 100); // 알록달록한 원 그리기 함수 호출

        glFlush();  // 화면 업데이트!

        glfwSwapBuffers(window); // 바로처리가되구여 (더블 버퍼링을 사용)
        glfwPollEvents();  //이번예쩨에선 안 쓰지만 보통이위치에잇으니가넣어봣구여 (사용자 입력(키보드, 마우스 등)을 처리)
    }

    glfwDestroyWindow(window);  //윈도우 파괴 = 윈도우 닫아죠
    glfwTerminate(); //컨텍스트 닫어 (메모리관리철저 메모리 누수가 너무 심해짐다. 3일동안 켜놔도 죽지않아야 하는 것이여)
    return 0;
}



/*컨텍스트(context) : OpenGL을 사용할 수 있도록 하는 환경임.
OpenGL은 자체적으로 창을 생성하거나 입력을 처리하는 기능을 제공하지 않기 때문에,
GLFW 같은 라이브러리를 활용하여 창을 만들고 OpenGL 컨텍스트를 생성 및 관리해야 함.*/



/*과제: 삼각형 하고 end 햇으니까 사각형 만들고 원도 만들어바 -
원 그리는 법 : 적분하듯이 그린다! 방법은 삼각형 여러개 그리는 것!
점 세개만 넣고 그렸으니 삼각형이 하나만 그려지지만 점 6개를 넣으면 두개 그려짐. 점 12개를 넣으면 삼각형 3개 그려짐.
색은 아무렇게나! 색 직접 컨트롤은 나중에 배울지도. 그것까지 배우면 게임만드는것도 가능.*/
//다음 시간전까지 원 하나 그리는 과제를 깃에제출! PowerDL, GLUT, SDL 같이 배우지도않은내용들어가잇으면 빵점처리하신대여..
//여러개 그렷음햇는데,, -> 여러개 그리는것도 가능하다는거군!



// +) 그냥 하얀 원
//void drawFilledCircle(float cx, float cy, float r, int num_segments) {
//
//    #ifndef M_PI
//    #define M_PI 3.14159265358979323846
//    #endif
//
//    glBegin(GL_TRIANGLE_FAN);
//
//    // 원의 중심점
//    glVertex2f(cx, cy);
//
//    for (int i = 0; i <= num_segments; i++) {
//        float theta = 2.0f * M_PI * i / num_segments; // 라디안 변환
//        float x = r * cos(theta);
//        float y = r * sin(theta);
//
//        glVertex2f(cx + x, cy + y);
//    }
//
//    glEnd();
//}