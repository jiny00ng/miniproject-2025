//// 전체 게임 요약
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <ctime>
//#include <cstdlib>
//#include <chrono>
//#include <algorithm>
//#include <numeric>  // accumulate 사용
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
//    bool gameRunning = true;
//
//    while (gameRunning) {
//        vector<double> typingSpeeds;
//        vector<double> accuracies;
//        vector<double> times;
//        auto total_start_time = high_resolution_clock::now(); // 전체 소요 시간 시작
//
//        for (const string& original : sentences) {
//            string userInput;
//            bool isCorrect = false;
//
//            cout << "입력할 문장: " << original << endl;
//            auto start_time = high_resolution_clock::now();
//
//            while (!isCorrect) {
//                cout << "> ";
//                getline(cin, userInput);
//
//                auto end_time = high_resolution_clock::now();
//                duration<double> elapsed = end_time - start_time;
//                double typingSpeed = userInput.length() / elapsed.count() * 60;
//                double elapsedTime = elapsed.count(); // 소요 시간 (초)
//
//                string originalWithoutSpaces = removeSpaces(original);
//                string userInputWithoutSpaces = removeSpaces(userInput);
//
//                if (originalWithoutSpaces == userInputWithoutSpaces) {
//                    isCorrect = true;
//                    double accuracy = calculateAccuracy(original, userInput);
//
//                    typingSpeeds.push_back(typingSpeed);
//                    accuracies.push_back(accuracy);
//                    times.push_back(elapsedTime);
//
//                    cout << "정확합니다!" << endl;
//                    cout << "----------------------------------\n";
//                    cout << "타자 속도: " << typingSpeed << " 타/분(WPM)" << endl;
//                    cout << "정확도: " << accuracy << "%" << endl;
//                    cout << "소요 시간: " << elapsedTime << " 초\n" << endl;
//                }
//                else {
//                    cout << "틀렸습니다. 다시 입력하세요." << endl;
//                }
//            }
//        }
//
//        auto total_end_time = high_resolution_clock::now(); // 전체 소요 시간 종료
//        duration<double> total_elapsed = total_end_time - total_start_time;
//        double totalTime = total_elapsed.count(); // 총 소요 시간 (초)
//
//        // 평균 속도 및 정확도 계산
//        double avgSpeed = accumulate(typingSpeeds.begin(), typingSpeeds.end(), 0.0) / typingSpeeds.size();
//        double avgAccuracy = accumulate(accuracies.begin(), accuracies.end(), 0.0) / accuracies.size();
//        double avgTime = accumulate(times.begin(), times.end(), 0.0) / times.size();
//
//        cout << "----------------------------------\n";
//        cout << " 전체 결과 요약\n";
//        cout << "----------------------------------\n";
//        cout << " 평균 타자 속도: " << avgSpeed << " 타/분(WPM)\n";
//        cout << " 평균 정확도: " << avgAccuracy << "%\n";
//        cout << " 평균 소요 시간: " << avgTime << " 초\n";
//        cout << " 총 소요 시간: " << totalTime << " 초\n";
//        cout << "----------------------------------\n";
//
//        char restartChoice;
//        cout << "모든 문장을 완료했습니다. 다시 하시겠습니까? (y/n): ";
//        cin >> restartChoice;
//        cin.ignore(numeric_limits<streamsize>::max(), '\n');
//
//        if (restartChoice == 'n' || restartChoice == 'N') {
//            gameRunning = false;
//            cout << "게임 종료!" << endl;
//        }
//    }
//    return 0;
//}
