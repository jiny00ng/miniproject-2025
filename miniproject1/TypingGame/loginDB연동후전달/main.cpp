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
        std::cout << "�α��� ����! ���� ID: " << userID << std::endl;
    }
    else {
        std::cout << "�α��� ���� �Ǵ� â ����" << std::endl;
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
//    // �α��� ���� ó��
//    sf::RenderWindow loginWindow(sf::VideoMode(sf::Vector2u(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)), L"Login");
//    MySQLConnector db;
//    std::string userID;
//    if (!showLoginWindow(loginWindow, db, userID)) {
//        return 0;  // �α��� ���� �Ǵ� â �ݱ� �� ����
//    }
//
//    // �α��� ���� �� ���� ���� UI ����
//    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)), L"���� ���� ȭ��");
//    sf::Font font;
//    NetworkManager client;
//    GameManager game;
//    Texture typingButtonTexture, matchButtonTexture, korButtonTexture;
//
//    if (!font.openFromFile("D2Coding.ttf")) {
//        std::cerr << "��Ʈ �ε� ����!" << std::endl;
//        return -1;
//    }
//
//    if (!typingButtonTexture.loadFromFile("./assets/image/button.png")) {
//        cerr << "Typing ��ư �̹��� �ε� ����!" << endl;
//        return -1;
//    }
//    if (!matchButtonTexture.loadFromFile("./assets/image/button.png")) {
//        cerr << "Match ��ư �̹��� �ε� ����!" << endl;
//        return -1;
//    }
//    if (!korButtonTexture.loadFromFile("./assets/image/button.png")) {
//        cerr << "koreng ��ư �̹��� �ε� ����!" << endl;
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
//    Text korengButtonText(font, L"�ѱ� Ÿ�� ����");
//    korengButtonText.setPosition(Vector2f(400.f, 200.f));
//    korengButtonText.setCharacterSize(30);
//    korengButtonText.setFillColor(Color::Black);
//
//    Sprite typingButtonSprite(typingButtonTexture);
//    typingButtonSprite.setScale(Vector2(scaleX, scaleY));
//    typingButtonSprite.setTexture(typingButtonTexture);
//    typingButtonSprite.setPosition(Vector2f(320.f, 290.f));
//
//    Text typingButtonText(font, L"���� Ÿ�� ����");
//    typingButtonText.setPosition(Vector2f(400.f, 300.f));
//    typingButtonText.setCharacterSize(30);
//    typingButtonText.setFillColor(Color::Black);
//
//    Sprite matchButtonSprite(typingButtonTexture);
//    matchButtonSprite.setScale(Vector2(scaleX, scaleY));
//    matchButtonSprite.setTexture(typingButtonTexture);
//    matchButtonSprite.setPosition(Vector2f(320.f, 390.f));
//
//    Text matchButtonText(font, L"�ڵ� ���");
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
//                        std::cout << "�ε�â ����!!" << std::endl;
//                        });
//
//                    if (client.waitForMatch(window, font)) {
//                        isMatching = true;
//                        if (loadingThread.joinable()) loadingThread.join();
//                        std::cout << "��ġ �Ϸ�Ǿ���!!" << std::endl;
//                        std::cout << "���� ����!!" << std::endl;
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
