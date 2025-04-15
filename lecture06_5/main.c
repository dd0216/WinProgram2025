

// 마우스 상태 가져오기
if (GetCursorPos(&mousePos)) {
    // 마우스 왼쪽 버튼 클릭 상태 확인
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
        isDragging = 1; // 드래그 시작
    }
    else {
        isDragging = 0; // 드래그 중지
    }

    원래 이렇게 했다가, 이러면 그냥 아무데서나 드래그하면 o가 마우스 위치로 옮겨지더라고..그러면 그건 o 드래그하기가 아니잖소

    마우스가 문자 위에서 드래그를 시작하지 않은 경우엔 드래그가 되지 않도록 하기 위해
    문자 위치와 마우스 클릭 위치를 비교하여 드래그를 시작할지 결정해야 함...
    아래가 해당 기능을 추가한 코드임...
        설명: 드래그 시작 조건이 더 빢빢하게 추가됨.
        if (!isDragging && mousePos.x / 9 == letterX && mousePos.y / 19 - 1 == letterY)
        위 조건을 추가하여 마우스가 문자 위치에서 드래그를 시작해야만 isDragging 값을 1로 설정하기로..
        마우스 좌표와 문자 좌표를 비교하여 드래그 가능 여부를 결정.

        while (1) {
            // 화면 갱신 (드래그 중일 때만 위치 변경)
            system("cls");  // 화면 초기화
            printf("알파벳 '%c'을 마우스로 드래그하세요.\n", letter);
            printf("현재 알파벳 '%c'의 위치: (%d, %d)\n", letter, letterX, letterY);

            // 알파벳 O 출력
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { letterX, letterY });
            printf("%c", letter);

            // 마우스 상태 가져오기
            if (GetCursorPos(&mousePos)) {
                // 마우스 왼쪽 버튼 클릭 상태 확인
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    // 문자 위치 확인 (드래그 시작 조건 추가)
                    if (!isDragging && mousePos.x / 9 == letterX && mousePos.y / 19 - 1 == letterY) {
                        isDragging = 1; // 드래그 시작
                    }
                }
                else {
                    isDragging = 0; // 드래그 중지
                }

                // 드래그 중일 때만 문자 위치 업데이트
                if (isDragging) {
                    letterX = mousePos.x / 9;
                    letterY = mousePos.y / 19 - 1;  // 타이틀 바를 고려한 위치 조정
                }
            }


            근데 이제 ... 이게 마우스의 위치와 문자의 위치가 정확히 일치하기가 좀 어렵고 그래서
            그 움직이게 하는 허용 범위를 쪼금씪만 더 위아래양옆으로 좀 늘리고 싶어서
            마우스 위치와 문자의 위치가 완벽히 일치하지 않아도 드래그를 시작할 수 있게해서 사용자 경험을 개선
            허용 범위를 조금 더 늘리려면, 마우스 위치와 문자 위치를 비교하는 조건에 범위 조건을 추가하면 됩다.
            즉, 마우스 위치가 문자 위치 근처(상하좌우로 일정 거리 내)에 있을 때 드래그를 시작하도록 설정할 수 있음.
            아래는 수정된 코드입니다 :

        설명: 주요 변경 사항 :
            dragRange 변수 추가 : 허용 범위를 설정하는 변수로, 문자 주변 상하좌우 dragRange 텍스트 셀 내에서 드래그 가능하게 만듬.
                예) dragRange = 2 : 문자 위치를 중심으로 상하좌우로 2칸 이내에서 드래그 가능.

            범위 조건 추가 :
                mouseX와 mouseY가 letterX 및 letterY에서 일정 범위(dragRange) 안에 있을 때만 isDragging을 활성화.


                    // 현재 마우스 위치 가져옴. 성공하면 내부 코드 실행함.
                    if (GetCursorPos(&mousePos)) {
                        // 마우스 왼쪽 버튼 눌림 상태 확인함.
                        // 0x8000은 눌림 상태 나타냄.
                        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                            // 마우스가 문자 근처에 있으면 드래그 시작 조건 설정함.
                            // 마우스 X, Y 위치를 픽셀에서 텍스트 셀로 변환함.
                            int mouseX = mousePos.x / 9;       // 마우스 X 좌표 텍스트 셀로 변환함.
                            int mouseY = mousePos.y / 19 - 1; // 마우스 Y 좌표 텍스트 셀로 변환, 타이틀 바 고려해서 조정함.

                            // 드래그 중 아니고 마우스가 문자의 근처 범위 안에 있을 때 드래그 시작함.
                            if (!isDragging &&
                                mouseX >= (letterX - dragRange) && mouseX <= (letterX + dragRange) &&  // X 범위 검사.
                                mouseY >= (letterY - dragRange) && mouseY <= (letterY + dragRange)) { // Y 범위 검사.
                                isDragging = 1; // 드래그 상태 활성화.
                            }
                        }
                        else {
                            // 마우스 왼쪽 버튼 안 눌렸으면 드래그 상태 비활성화.
                            isDragging = 0;
                        }

                        // 드래그 중이면 마우스 위치에 따라 문자의 위치 업데이트함.
                        if (isDragging) {
                            letterX = mousePos.x / 9;       // 마우스 X 좌표 따라 문자 X 위치 설정함.
                            letterY = mousePos.y / 19 - 1; // 마우스 Y 좌표 따라 문자 Y 위치 설정, 타이틀 바 고려해서 조정!
                        }
                    }




            끝-!(하얀 텍스트 블록처리를 없앨수있따고 하는 퀵 에디트 모드(Quick Edit Mode)를 없애는 함수를 넣어봣는데
                안되고그대로여서... 포기햇다.......)