#include <SFML/Graphics.hpp>
#include <thread>
#include "userManager.h"
#include "LoginUI.h"
#include <iostream>
#include "RankingUI.h"

using namespace std;
using namespace sf;

bool showStartScreen(sf::RenderWindow& window);  // 함수 원형 선언
bool showRankingUI = false;
bool loggedOut = false;  // 로그아웃 여부를 확인하는 변수

int main() {
    int MAIN_WINDOW_WIDTH = 1280;
    int MAIN_WINDOW_HEIGHT = 720;
    sf::RenderWindow gameWindow(sf::VideoMode(sf::Vector2u(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)), L"타자 연습 게임");

    MySQLConnector db;
    std::string userID;
    bool loggedIn = false;

    RankingUI rankingUI;  // RankingUI 객체를 계속 유지

    sf::Font font;
    if (!font.openFromFile("assets/fonts/D2Coding.ttf")) {
        std::cerr << "폰트 로드 실패!" << std::endl;
        return -1;
    }

    // 랭킹 아이콘 로드
    sf::Texture rankingIconTexture;
    if (!rankingIconTexture.loadFromFile("assets/images/ranking_icon2.png")) {  // 아이콘 이미지 파일 경로
        std::cerr << "아이콘 이미지 로드 실패!" << std::endl;
        return -1;
    }
    sf::Sprite rankingIcon(rankingIconTexture);
    rankingIcon.setPosition(Vector2f(MAIN_WINDOW_WIDTH - 120, 10));  // 오른쪽 상단에 배치

    // 아이콘 크기 조정 (여기서는 0.5배 크기로 설정)
    rankingIcon.setScale({ 0.2f, 0.2f });  // X, Y 배율을 각각 0.5로 설정하여 크기 반으로 조정
    
    // 수정: 로그아웃 버튼 이미지
    sf::Texture logoutButtonTexture;
    if (!logoutButtonTexture.loadFromFile("assets/images/logout.png")) {
        std::cerr << "로그아웃 버튼 이미지 로드 실패!" << std::endl;
        return -1;
    }
    sf::Sprite logoutButton(logoutButtonTexture);

    // 스케일 먼저 적용
    logoutButton.setScale({ 0.1f, 0.1f });  // 필요시 크기 조절

    // 스케일 적용 후 정확한 크기 가져오기
    FloatRect buttonBounds = logoutButton.getGlobalBounds();

    // 위치: 화면 하단 중앙에, 아래에서 안 띄우기
    logoutButton.setPosition({
        MAIN_WINDOW_WIDTH / 2.f - buttonBounds.size.x / 2.f,
        MAIN_WINDOW_HEIGHT - buttonBounds.size.y
        });

    // 로그인 창 실행 전에 추가
    if (!showStartScreen(gameWindow)) {
        return 0;  // 사용자가 창을 닫은 경우 종료
    }

    // 🔹 로그인 창 실행
    while (gameWindow.isOpen()) {
        while (const std::optional<Event> event = gameWindow.pollEvent()) {
            if (event->is<Event::Closed>()) {
                gameWindow.close();
            }

            if (event->is<Event::MouseButtonPressed>()) {
                Vector2i mousePos = Mouse::getPosition(gameWindow);
                if (rankingIcon.getGlobalBounds().contains(Vector2f(mousePos.x, mousePos.y))) {
                    showRankingUI = true;
                }

                // 로그아웃 버튼 클릭 시
                if (logoutButton.getGlobalBounds().contains(Vector2f(mousePos.x, mousePos.y))) {
                    loggedIn = false;  // 로그인 상태 초기화
                    loggedOut = true;  // 로그아웃 플래그 설정
                }
            }
        }

        gameWindow.clear();

        if (!loggedIn) {
            // 로그인 UI를 표시
            if (showLoginWindow(gameWindow, db, userID)) {
                std::cout << "로그인 성공! 유저 ID: " << userID << std::endl;
                loggedIn = true;
            }
            else {
                // 로그인 화면에서 랭킹 아이콘도 표시
                gameWindow.draw(rankingIcon);
            }
        }
        else {
            // 로그인 성공 후 게임 화면 표시
            sf::Text welcomeText(font, L"타자연습 게임", 50);
            welcomeText.setFillColor(sf::Color::White);
            welcomeText.setPosition(Vector2f(MAIN_WINDOW_WIDTH / 2 - welcomeText.getGlobalBounds().size.x / 2, MAIN_WINDOW_HEIGHT / 2 - 350));
            gameWindow.draw(welcomeText);

            // 게임 화면에서 랭킹 아이콘과 로그아웃 버튼도 그려주기
            gameWindow.draw(rankingIcon);
            gameWindow.draw(logoutButton);
        }

        gameWindow.display();

        // 랭킹 UI를 별도 스레드에서 실행
        if (showRankingUI) {
            std::thread rankingThread([&]() {
                rankingUI.show();  // 랭킹 UI를 별도의 스레드에서 실행
                });
            rankingThread.detach();  // 스레드가 종료될 때까지 기다리지 않도록 분리
            showRankingUI = false;
        }

        // 로그아웃 플래그가 true이면 로그인 화면으로 돌아감
        if (loggedOut) {
            gameWindow.clear();
            loggedOut = false;  // 로그아웃 상태 초기화
        }
    }

    return 0;
}
