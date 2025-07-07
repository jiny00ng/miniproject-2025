// 콘솔창에서 결과 출력
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <numeric> // accumulate

using namespace std;
using namespace sf;
using namespace chrono;

// 문장을 파일에서 불러오는 함수
vector<string> loadSentences(const string& filename) {
    vector<string> sentences;
    ifstream file(filename);        // 파일 읽기 모드 여는 객체 생성
    if (!file) {
        cerr << "파일을 열 수 없습니다: " << filename << endl;
        exit(1); // 파일이 열리지 않으면 프로그램 종료
    }
    string line;
    while (getline(file, line)) {
        if (!line.empty()) sentences.push_back(line); // 파일에서 한 줄씩 읽어와 문장 벡터에 저장
    }
    return sentences;
}

// 정확도 계산 함수 (백스페이스를 고려한 정확도 계산)
double calculateAccuracyWithBackspace(int totalTyped, int backspaceCount) {
    return 100.0 * (totalTyped - backspaceCount) / totalTyped; // 타이핑한 글자 수에서 백스페이스 횟수를 제외한 값으로 정확도를 계산
}

int main() {
    try {
        cerr << "Program started!" << endl;

        // SFML 윈도우 설정
        Font font;
        if (!font.openFromFile("assets/fonts/D2Coding.ttf")) {  // 폰트 로드
            cerr << "폰트 로드 실패!" << endl;
            return 1; // 폰트가 로드되지 않으면 프로그램 종료
        }

        // SFML 창 생성 (800x400 크기)
        RenderWindow window(VideoMode({ 800, 400 }), "Typing Practice Game");

        vector<string> sentences;
        try {
            sentences = loadSentences("aegukga.txt");  // 문장 파일 불러오기
        }
        catch (const exception& e) {
            cerr << "오류 발생: " << e.what() << endl;
            return 1;  // 문장 파일을 불러올 수 없으면 종료
        }

        bool gameRunning = true; // 게임이 실행 중인지를 나타내는 변수

        while (gameRunning) {
            vector<double> typingSpeeds; // 타자 속도를 저장할 벡터
            vector<double> accuracies;  // 정확도를 저장할 벡터
            vector<double> times;       // 소요 시간을 저장할 벡터
            auto total_start_time = high_resolution_clock::now(); // 전체 소요 시간 시작

            // 각 문장에 대해 반복
            for (const string& original : sentences) {
                string userInput;  // 사용자가 입력한 텍스트
                bool isCorrect = false; // 타이핑이 맞았는지 여부
                int backspaceCount = 0; // 백스페이스 횟수
                int totalCharsTyped = 0; // 타이핑한 총 글자 수

                // SFML 텍스트 설정
                Text sentenceText(font, original, 24); // 문장을 화면에 출력
                sentenceText.setPosition({ 50, 100 });
                sentenceText.setFillColor(Color::White); // 문자는 흰색

                Text userText(font, "", 24); // 사용자가 입력한 텍스트를 화면에 출력
                userText.setPosition({ 50, 150 });
                userText.setFillColor(Color::Green); // 초기에 녹색으로 설정

                // 콘솔 출력: 입력할 문장 출력
                cout << "입력할 문장: " << original << endl;
                auto start_time = high_resolution_clock::now(); // 타이핑 시작 시간

                // 타이핑이 맞을 때까지 반복
                while (!isCorrect) {
                    cout << "> ";
                    // 이벤트 처리 (창이 닫히는지 체크)
                    while (const optional event = window.pollEvent()) {
                        if (event->is<Event::Closed>()) {
                            window.close();
                        }
                    }

                    window.clear(Color::Black); // 화면을 검정색으로 초기화
                    window.draw(sentenceText); // 문장 출력
                    window.draw(userText);     // 사용자 입력 텍스트 출력
                    window.display();          // 화면에 변경 사항 반영

                    userInput.clear();         // 사용자 입력 초기화
                    backspaceCount = 0;        // 백스페이스 횟수 초기화
                    totalCharsTyped = 0;       // 타이핑한 글자 수 초기화

                    // 문자 입력 받기 (백스페이스와 일반 문자 처리)
                    while (true) {
                        char ch;
                        cin.get(ch); // 사용자가 입력한 문자

                        if (ch == '\n') break; // 엔터 입력 시 종료

                        if (ch == '\b' || ch == 127) { // 백스페이스 처리 (127은 일부 OS에서 백스페이스 코드)
                            if (!userInput.empty()) {
                                userInput.pop_back(); // 마지막 글자 삭제
                                backspaceCount++;      // 백스페이스 횟수 증가
                            }
                        }
                        else {
                            userInput += ch;       // 문자 입력받기
                            totalCharsTyped++;      // 타이핑한 글자 수 증가
                        }

                        // 입력 텍스트 색상 업데이트: 문장이 정확하게 입력되었는지 확인
                        if (original.rfind(userInput, 0) == 0) {
                            userText.setFillColor(Color::Green); // 일치하면 녹색
                        }
                        else {
                            userText.setFillColor(Color::Red); // 불일치하면 빨간색
                        }
                        userText.setString(userInput); // 화면에 사용자 입력 텍스트 반영
                    }

                    // 타이핑이 끝나고 시간 측정
                    auto end_time = high_resolution_clock::now();
                    duration<double> elapsed = end_time - start_time;
                    double typingSpeed = (userInput.length() / 5.0) / elapsed.count() * 60; // 단어 기준 WPM 계산
                    double elapsedTime = elapsed.count(); // 소요 시간 (초)

                    // 사용자가 입력한 텍스트와 원본 문장이 동일한지 확인
                    if (original == userInput) {
                        isCorrect = true; // 입력이 정확하면 종료
                        double accuracy = calculateAccuracyWithBackspace(totalCharsTyped, backspaceCount); // 정확도 계산

                        // 성과 기록
                        typingSpeeds.push_back(typingSpeed);
                        accuracies.push_back(accuracy);
                        times.push_back(elapsedTime);

                        // 결과 출력
                        cout << "정확합니다!" << endl;
                        cout << "----------------------------------\n";
                        cout << "타자 속도: " << typingSpeed << " WPM" << endl;
                        cout << "정확도: " << accuracy << "% (백스페이스 " << backspaceCount << "회 사용)" << endl;
                        cout << "소요 시간: " << elapsedTime << " 초\n" << endl;
                    }
                    else {
                        cout << "틀렸습니다. 다시 입력하세요." << endl; // 문장이 틀리면 다시 입력 받음
                    }
                }
            }

            // 전체 타이핑 소요 시간 계산
            auto total_end_time = high_resolution_clock::now();
            duration<double> total_elapsed = total_end_time - total_start_time;
            double totalTime = total_elapsed.count(); // 총 소요 시간 (초)

            // 평균 타자 속도, 정확도, 소요 시간 계산
            double avgSpeed = typingSpeeds.empty() ? 0 : accumulate(typingSpeeds.begin(), typingSpeeds.end(), 0.0) / typingSpeeds.size();
            double avgAccuracy = accuracies.empty() ? 0 : accumulate(accuracies.begin(), accuracies.end(), 0.0) / accuracies.size();
            double avgTime = times.empty() ? 0 : accumulate(times.begin(), times.end(), 0.0) / times.size();

            // 전체 결과 출력
            cout << "----------------------------------\n";
            cout << " 전체 결과 요약\n";
            cout << "----------------------------------\n";
            cout << " 평균 타자 속도: " << avgSpeed << " WPM\n";
            cout << " 평균 정확도: " << avgAccuracy << "%\n";
            cout << " 평균 소요 시간: " << avgTime << " 초\n";
            cout << " 총 소요 시간: " << totalTime << " 초\n";
            cout << "----------------------------------\n";

            // 게임을 다시 시작할지 여부를 묻는 메시지
            char restartChoice;
            cout << "모든 문장을 완료했습니다. 다시 하시겠습니까? (y/n): ";
            cin >> restartChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 남은 입력 버퍼 비우기

            // 예외 처리: 잘못된 입력에 대한 처리
            while (restartChoice != 'y' && restartChoice != 'Y' && restartChoice != 'n' && restartChoice != 'N') {
                cerr << "잘못된 입력입니다. 'y' 또는 'n'을 입력해 주세요." << endl;
                cout << "다시 시도하세요: ";
                cin >> restartChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (restartChoice == 'n' || restartChoice == 'N') {
                gameRunning = false; // 게임 종료
                cout << "게임 종료!" << endl;
            }

        }

        return 0;
    }
    // 예외 처리
    catch (const exception& e) {
        cerr << "예외 발생: " << e.what() << endl;
        return 1;
    }
    catch (...) {
        cerr << "알 수 없는 오류가 발생했습니다." << endl;
        return 1;
    }
}
