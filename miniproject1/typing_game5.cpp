//// 공백 포함 비교
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <ctime>
//#include <cstdlib>
//#include <chrono>   
//#include <algorithm>
//#include <numeric>
//#include <limits>
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
//        cerr << "파일을 열 수 없습니다! '" << filename << "' 파일을 확인하세요." << endl;
//        exit(1);
//    }
//
//    string line;
//    while (getline(file, line)) {
//        if (!line.empty()) { // 빈 줄 제외
//            sentences.push_back(line);
//        }
//    }
//    file.close();
//    return sentences;
//}
//
//// 백스페이스를 고려한 정확도 계산 함수
//double calculateAccuracyWithBackspace(int totalCharsTyped, int backspaceCount) {
//    if (totalCharsTyped == 0) return 0.0; // 입력이 없을 경우 정확도 0%
//    return ((double)(totalCharsTyped - backspaceCount) / totalCharsTyped) * 100;
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
//            int backspaceCount = 0;
//            int totalCharsTyped = 0;
//
//            cout << "입력할 문장: " << original << endl;
//            auto start_time = high_resolution_clock::now();
//
//            while (!isCorrect) {
//                cout << "> ";
//                char ch;
//                userInput.clear();
//                backspaceCount = 0;
//                totalCharsTyped = 0;
//
//                // 문자 입력 받기
//                while (true) {
//                    ch = cin.get();
//                    if (ch == '\n') break; // 엔터(Enter) 입력 시 종료
//
//                    if (ch == '\b' || ch == 127) { // 백스페이스 처리 (127은 일부 OS에서 백스페이스 코드)
//                        if (!userInput.empty()) {
//                            userInput.pop_back();
//                            backspaceCount++;
//                        }
//                    }
//                    else {
//                        userInput += ch;
//                        totalCharsTyped++;
//                    }
//                }
//
//                auto end_time = high_resolution_clock::now();
//                duration<double> elapsed = end_time - start_time;
//                double typingSpeed = (userInput.length() / 5.0) / elapsed.count() * 60; // 단어 기준 WPM
//                double elapsedTime = elapsed.count(); // 소요 시간 (초)
//
//                if (original == userInput) { // 공백 포함 정확 비교
//                    isCorrect = true;
//                    double accuracy = calculateAccuracyWithBackspace(totalCharsTyped, backspaceCount);
//
//                    typingSpeeds.push_back(typingSpeed);
//                    accuracies.push_back(accuracy);
//                    times.push_back(elapsedTime);
//
//                    cout << "정확합니다!" << endl;
//                    cout << "----------------------------------\n";
//                    cout << "타자 속도: " << typingSpeed << " WPM" << endl;
//                    cout << "정확도: " << accuracy << "% (백스페이스 " << backspaceCount << "회 사용)" << endl;
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
//        // 평균 속도 및 정확도 계산 (벡터가 비어 있을 경우 예외 처리)
//        double avgSpeed = typingSpeeds.empty() ? 0 : accumulate(typingSpeeds.begin(), typingSpeeds.end(), 0.0) / typingSpeeds.size();
//        double avgAccuracy = accuracies.empty() ? 0 : accumulate(accuracies.begin(), accuracies.end(), 0.0) / accuracies.size();
//        double avgTime = times.empty() ? 0 : accumulate(times.begin(), times.end(), 0.0) / times.size();
//
//        cout << "----------------------------------\n";
//        cout << " 전체 결과 요약\n";
//        cout << "----------------------------------\n";
//        cout << " 평균 타자 속도: " << avgSpeed << " WPM\n";
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
