//-------------------------------------------------------------test main
#include <SFML/Graphics.hpp>
#include "userManager.h"
#include "loginUI.h"

int main() {
    int MAIN_WINDOW_WIDTH = 1280;
    int MAIN_WINDOW_HEIGHT = 720;
    sf::RenderWindow loginWindow(sf::VideoMode(sf::Vector2u(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)), L"Login_test");

    MySQLConnector db;
    std::string userID;

    if (showLoginWindow(loginWindow, db, userID)) {
        std::cout << "로그인 성공! 유저 ID: " << userID << std::endl;
    }
    else {
        std::cout << "로그인 실패 또는 창 닫힘" << std::endl;
    }

    return 0;
}


//-------------------------------------------------------------main
//// main.cpp
//#include <SFML/Graphics.hpp>
//#include <SFML/Network.hpp>
//#include "networkManager.h"
//#include "gameManager.h"
//#include "UserManager.h"
//#include "loginUI.h"
//#include <iostream>
//#include <locale>
//#include <thread>
//#include <codecvt>
//#include <chrono>
//using namespace std;
//using namespace sf;
//
//int main() {
//    int MAIN_WINDOW_WIDTH = 1280;
//    int MAIN_WINDOW_HEIGHT = 720;
//
//    // 로그인 먼저 처리
//    sf::RenderWindow loginWindow(sf::VideoMode(sf::Vector2u(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)), L"Login");
//    MySQLConnector db;
//    std::string userID;
//    if (!showLoginWindow(loginWindow, db, userID)) {
//        return 0;  // 로그인 실패 또는 창 닫기 시 종료
//    }
//
//    // 로그인 성공 후 게임 메인 UI 실행
//    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)), L"게임 메인 화면");
//    sf::Font font;
//    NetworkManager client;
//    GameManager game;
//    Texture typingButtonTexture, matchButtonTexture, korButtonTexture;
//
//    if (!font.openFromFile("D2Coding.ttf")) {
//        std::cerr << "폰트 로드 실패!" << std::endl;
//        return -1;
//    }
//
//    if (!typingButtonTexture.loadFromFile("./assets/image/button.png")) {
//        cerr << "Typing 버튼 이미지 로드 실패!" << endl;
//        return -1;
//    }
//    if (!matchButtonTexture.loadFromFile("./assets/image/button.png")) {
//        cerr << "Match 버튼 이미지 로드 실패!" << endl;
//        return -1;
//    }
//    if (!korButtonTexture.loadFromFile("./assets/image/button.png")) {
//        cerr << "koreng 버튼 이미지 로드 실패!" << endl;
//        return -1;
//    }
//
//    Sprite korengButtonSprite(typingButtonTexture);
//    Vector2u textureSize = typingButtonTexture.getSize();
//    float scaleX = 50.f / textureSize.x;
//    float scaleY = 50.f / textureSize.y;
//    korengButtonSprite.setScale(Vector2(scaleX, scaleY));
//    korengButtonSprite.setTexture(typingButtonTexture);
//    korengButtonSprite.setPosition(Vector2f(320.f, 190.f));
//
//    Text korengButtonText(font, L"한글 타자 연습");
//    korengButtonText.setPosition(Vector2f(400.f, 200.f));
//    korengButtonText.setCharacterSize(30);
//    korengButtonText.setFillColor(Color::Black);
//
//    Sprite typingButtonSprite(typingButtonTexture);
//    typingButtonSprite.setScale(Vector2(scaleX, scaleY));
//    typingButtonSprite.setTexture(typingButtonTexture);
//    typingButtonSprite.setPosition(Vector2f(320.f, 290.f));
//
//    Text typingButtonText(font, L"영문 타자 연습");
//    typingButtonText.setPosition(Vector2f(400.f, 300.f));
//    typingButtonText.setCharacterSize(30);
//    typingButtonText.setFillColor(Color::Black);
//
//    Sprite matchButtonSprite(typingButtonTexture);
//    matchButtonSprite.setScale(Vector2(scaleX, scaleY));
//    matchButtonSprite.setTexture(typingButtonTexture);
//    matchButtonSprite.setPosition(Vector2f(320.f, 390.f));
//
//    Text matchButtonText(font, L"코딩 대결");
//    matchButtonText.setPosition(Vector2f(400.f, 400.f));
//    matchButtonText.setCharacterSize(30);
//    matchButtonText.setFillColor(Color::Black);
//
//    while (window.isOpen()) {
//        std::optional<Event> event;
//        while (const std::optional event = window.pollEvent()) {
//            if (event->is<sf::Event::Closed>())
//                window.close();
//
//            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
//                Vector2i mousePos = Mouse::getPosition(window);
//                if (matchButtonSprite.getGlobalBounds().contains(Vector2f(mousePos.x, mousePos.y))) {
//                    cout << "1:1 Match Button Clicked!" << endl;
//
//                    if (!client.connectToServer()) {
//                        return -1;
//                    }
//
//                    bool isMatching = false;
//                    std::thread loadingThread([&]() {
//                        game.showLoadingScreen(window, font, isMatching);
//                        std::cout << "로딩창 띄우기!!" << std::endl;
//                        });
//
//                    if (client.waitForMatch(window, font)) {
//                        isMatching = true;
//                        if (loadingThread.joinable()) loadingThread.join();
//                        std::cout << "매치 완료되었슴!!" << std::endl;
//                        std::cout << "게임 시작!!" << std::endl;
//                        game.runGame(window, font);
//                    }
//                }
//            }
//        }
//
//        window.clear(Color::White);
//        window.draw(typingButtonSprite);
//        window.draw(typingButtonText);
//        window.draw(matchButtonSprite);
//        window.draw(matchButtonText);
//        window.draw(korengButtonSprite);
//        window.draw(korengButtonText);
//        window.display();
//    }
//    return 0;
//}
