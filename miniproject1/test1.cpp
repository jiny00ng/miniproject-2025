// 실시간 문자입력 및 백스페이스 처리
//#include <iostream>
//#include <string>
//#include <conio.h>  // _kbhit(), _getch() 사용을 위해 포함
//
//using namespace std;
//
//int main() {
//    string targetText = "Hello, welcome to typing practice!";
//    string userInput;
//    int backspaceCount = 0;
//    int correctCount = 0;
//    int incorrectCount = 0;
//
//    cout << "타자 연습 게임 시작!" << endl;
//    cout << "목표 텍스트: " << targetText << endl;
//
//    while (true) {
//        userInput = "";
//        int i = 0;
//
//        // 사용자 입력 받기
//        while (i < targetText.length()) {
//            char ch = _getch();  // 사용자가 입력한 문자
//            if (ch == 8) {  // 백스페이스 처리
//                if (i > 0) {
//                    userInput = userInput.substr(0, userInput.length() - 1);
//                    backspaceCount++;
//                    i--;  // 문자 수 감소
//                }
//            }
//            else {
//                userInput += ch;
//                if (userInput[i] == targetText[i]) {
//                    correctCount++;
//                }
//                else {
//                    incorrectCount++;
//                }
//                i++;
//            }
//
//            // 실시간으로 입력한 텍스트를 출력
//            cout << "\r입력한 텍스트: " << userInput << " ";
//            cout.flush();
//        }
//
//        // 정확도 계산
//        int totalTyped = correctCount + incorrectCount;
//        double accuracy = (totalTyped > 0) ? (correctCount / (double)totalTyped) * 100 : 0;
//
//        // 결과 출력
//        cout << endl << "게임 종료!" << endl;
//        cout << "정확도: " << accuracy << "%" << endl;
//        cout << "백스페이스 횟수: " << backspaceCount << endl;
//
//        cout << "다시 하시겠습니까? (y/n): ";
//        char playAgain = _getch();
//        if (playAgain != 'y' && playAgain != 'Y') {
//            break;
//        }
//
//        // 초기화
//        correctCount = 0;
//        incorrectCount = 0;
//        backspaceCount = 0;
//    }
//
//    return 0;
//}
