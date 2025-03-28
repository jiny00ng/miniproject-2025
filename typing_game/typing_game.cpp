// SFML 3.0, C++20으로 적용
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <optional>
using namespace std;
using namespace chrono;

// 파일에서 문장을 불러오는 함수
vector<string> loadSentences(const string& filename) {
    vector<string> sentences;
    ifstream file(filename);

    if (!file) {
        cerr << "파일을 열 수 없습니다! 'aegukga.txt' 파일을 확인하세요." << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        sentences.push_back(line);
    }
    file.close();
    return sentences;
}

// Levenshtein Distance (편집 거리) 계산 함수
int levenshteinDistance(const string& s1, const string& s2) {
    int len1 = s1.size(), len2 = s2.size();
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

    for (int i = 0; i <= len1; i++) dp[i][0] = i;
    for (int j = 0; j <= len2; j++) dp[0][j] = j;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = min({ dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1 });
            }
        }
    }
    return dp[len1][len2];
}

// 문자열 정확도(%) 계산 함수
double calculateAccuracy(const string& original, const string& input) {
    int distance = levenshteinDistance(original, input);
    int maxLength = max(original.length(), input.length());
    return (1.0 - (double)distance / maxLength) * 100;
}

// 문자열에서 모든 공백 제거 함수
string removeSpaces(const string& str) {
    string result = str;
    result.erase(remove(result.begin(), result.end(), ' '), result.end());
    return result;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    vector<string> sentences = loadSentences("aegukga.txt");

    if (sentences.empty()) {
        std::cout << "파일에 문장이 없습니다!" << endl;
        return 1;
    }

    // SFML 창 생성
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), L"타자 연습 게임");
    window.setFramerateLimit(60);

    // 텍스트 객체
    const sf::Font font("assets/fonts/d2coding.ttf");
    sf::Text text(font, "Hello SFML", 50);
    
    
    if (!font.openFromFile("assets/fonts/d2coding.ttf")) {  // 폰트 파일이 있어야 합니다.
        cout << L"폰트 파일을 로드할 수 없습니다." << endl;
        return 1;
    }

    sf::Text text(" 한글임", font, 24);
    
    text.setFillColor(sf::Color::White);
    text.setPosition({200.f , 200.f});

    /*sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::White);*/
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        system("cls");

        for (const string& original : sentences) {
            string userInput;
            bool isCorrect = false;

            text.setString(L"입력할 문장: ");
            text.setString(original);
            inputText.setString(L"입력한 값: ");    //  userInput

            // 게임 루프
            auto start_time = high_resolution_clock::now();
            while (!isCorrect && window.isOpen()) {
                window.clear(sf::Color::Black);
                window.draw(text);
                window.draw(inputText);
                window.display();

                sf::Event keyEvent;
                while (window.pollEvent(keyEvent)) {
                    if (keyEvent.type == sf::Event::TextEntered) {
                        if (keyEvent.text.unicode == 8 && userInput.size() > 0) {
                            userInput.pop_back(); // Backspace 처리
                        }
                        else if (keyEvent.text.unicode < 128) {
                            userInput += static_cast<char>(keyEvent.text.unicode);
                        }
                    }
                    if (keyEvent.type == sf::Event::Closed) {
                        window.close();
                    }
                }

                // 타자 속도 계산
                auto end_time = high_resolution_clock::now();
                duration<double> elapsed = end_time - start_time;
                double typingSpeed = userInput.length() / elapsed.count() * 60;

                // 정확도 계산
                string originalWithoutSpaces = removeSpaces(original);
                string userInputWithoutSpaces = removeSpaces(userInput);

                if (originalWithoutSpaces == userInputWithoutSpaces) {
                    isCorrect = true;
                    text.setFillColor(sf::Color::Green);
                    inputText.setFillColor(sf::Color::Green);
                }
                else {
                    text.setFillColor(sf::Color::Red);
                    inputText.setFillColor(sf::Color::Red);
                }

                inputText.setString("입력한 값: " + userInput);
                window.clear();
                window.draw(text);
                window.draw(inputText);
                window.display();
            }

            // 게임 종료 방지
            char choice;
            cout << "\n전체 문장을 다 입력하셨습니다. 다시 하시겠습니까? (y/n): ";
            cin >> choice;
            if (choice == 'n' || choice == 'N')
                break;
        }

        window.close();
    }

    cout << "게임 종료!" << endl;
    return 0;
}
