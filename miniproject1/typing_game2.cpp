///* 입력값이 달라도 다음 값으로 넘어감 */
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <ctime>
//#include <cstdlib>
//#include <chrono>
//#include <conio.h>
//#include <algorithm>
//
//using namespace std;
//using namespace chrono;
//
//// 파일에서 문장을 불러오는 함수
//vector<string> loadSentences(const string& filename) {
//    vector<string> sentences;
//    ifstream file(filename);
//
//    if (!file) {
//        cerr << "파일을 열 수 없습니다! 'aegukga.txt' 파일을 확인하세요." << endl;
//        exit(1);
//    }
//
//    string line;
//    while (getline(file, line)) {
//        sentences.push_back(line);
//    }
//    file.close();
//    return sentences;
//}
//
//// Levenshtein Distance (편집 거리) 계산 함수
//int levenshteinDistance(const string& s1, const string& s2) {
//    int len1 = s1.size(), len2 = s2.size();
//    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
//
//    for (int i = 0; i <= len1; i++) dp[i][0] = i;
//    for (int j = 0; j <= len2; j++) dp[0][j] = j;
//
//    for (int i = 1; i <= len1; i++) {
//        for (int j = 1; j <= len2; j++) {
//            if (s1[i - 1] == s2[j - 1]) {
//                dp[i][j] = dp[i - 1][j - 1];
//            }
//            else {
//                dp[i][j] = min({ dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1 });
//            }
//        }
//    }
//    return dp[len1][len2];
//}
//
//// 문자열 정확도(%) 계산 함수
//double calculateAccuracy(const string& original, const string& input) {
//    int distance = levenshteinDistance(original, input);
//    int maxLength = max(original.length(), input.length());
//    return (1.0 - (double)distance / maxLength) * 100;
//}
//
//// 문자열에서 모든 공백 제거 함수
//string removeSpaces(const string& str) {
//    string result = str;
//    result.erase(remove(result.begin(), result.end(), ' '), result.end());
//    return result;
//}
//
//int main() {
//    srand(static_cast<unsigned int>(time(0)));
//    vector<string> sentences = loadSentences("aegukga.txt");
//
//    if (sentences.empty()) {
//        cout << "파일에 문장이 없습니다!" << endl;
//        return 1;
//    }
//
//    while (true) {
//        system("cls");
//
//        for (const string& original : sentences) {
//            cout << "\n[애국가 타자 연습]" << endl;
//            cout << "입력할 문장:\n" << original << endl;
//
//            cout << "\n(입력을 시작하면 시간 측정이 시작됩니다.)" << endl;
//            cout << "입력 > ";
//
//            while (!_kbhit());
//            auto start_time = high_resolution_clock::now();
//
//            cin.ignore();
//            string userInput;
//            getline(cin, userInput);
//
//            // 양쪽 공백 및 모든 공백 제거 후 비교
//            string originalWithoutSpaces = removeSpaces(original);
//            string userInputWithoutSpaces = removeSpaces(userInput);
//
//            auto end_time = high_resolution_clock::now();
//            duration<double> elapsed = end_time - start_time;
//            double typingSpeed = userInput.length() / elapsed.count() * 60;
//
//            // 정확히 일치하는지 확인 (공백 제거 후 비교)
//            if (originalWithoutSpaces == userInputWithoutSpaces) {
//                cout << "\n[결과]" << endl;
//                cout << "정확히 일치합니다!" << endl;
//                cout << "타자 속도: " << typingSpeed << " 타/분(WPM)" << endl;
//                cout << "소요 시간: " << elapsed.count() << " 초" << endl;
//            }
//            else {
//                double accuracy = calculateAccuracy(original, userInput);
//                cout << "\n[결과]" << endl;
//                cout << "정확도: " << accuracy << "%" << endl;
//                cout << "타자 속도: " << typingSpeed << " 타/분(WPM)" << endl;
//                cout << "소요 시간: " << elapsed.count() << " 초" << endl;
//            }
//        }
//
//        cout << "\n전체 문장을 다 입력하셨습니다. 다시 하시겠습니까? (y/n): ";
//        char choice;
//        cin >> choice;
//        if (choice == 'n' || choice == 'N')
//            break;
//    }
//
//    cout << "게임 종료!" << endl;
//    return 0;
//}
//
