// loginUI.cpp
#include "userManager.h"
#include "RankingUI.h"  
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>

#include <string>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace sf;
using namespace chrono;

void showSignupWindow(sf::RenderWindow& window, MySQLConnector& db);

bool showLoginWindow(RenderWindow& window, MySQLConnector& db, std::string& userID) {
    string id, password;
    bool isIdActive = false, isPassActive = false, showPassword = false;

    Font font;
    font.openFromFile("assets/fonts/D2Coding.ttf");

    // 창 크기 설정
    Vector2f windowSize(1280, 720);
    window.create(VideoMode({ static_cast<unsigned int>(windowSize.x),
        static_cast<unsigned int>(windowSize.y) }),
        L"타자연습 게임");

    // 배경 이미지 로딩
    Texture bgTexture;
    if (!bgTexture.loadFromFile("assets/images/login.png")) {
        cerr << "로그인 배경 이미지 로딩 실패!" << endl;
        return false;
    }
    Sprite background(bgTexture);
    background.setScale(Vector2f(
        windowSize.x / static_cast<float>(bgTexture.getSize().x),
        windowSize.y / static_cast<float>(bgTexture.getSize().y)
    ));

    // 수정: 버튼 이미지 로딩
    Texture loginBtnTex, signupBtnTex;
    if (!loginBtnTex.loadFromFile("assets/images/login_button.png") ||
        !signupBtnTex.loadFromFile("assets/images/signup_button.png")) {
        cerr << "버튼 이미지 로드 실패!" << endl;
        return false;
    }

    Sprite loginButton(loginBtnTex);
    loginButton.setScale({ 0.2f, 0.2f });
    loginButton.setPosition({ 330.f, 470.f });

    Sprite signupButton(signupBtnTex);
    signupButton.setScale({ 0.2f, 0.2f });
    signupButton.setPosition({ 530.f, 470.f });

    // 로그인 입력 UI
    float leftX = 330;
    float shiftY = 100;

    Text status(font, "", 24);
    status.setPosition({ leftX, 160 + shiftY });
    status.setFillColor(Color::Red);

    RectangleShape inputBox(Vector2f(400, 50));
    inputBox.setFillColor(Color::White);
    inputBox.setOutlineColor(Color::Black);
    inputBox.setOutlineThickness(2);

    RectangleShape idBox = inputBox, passBox = inputBox;
    idBox.setPosition({ leftX, 200 + shiftY });
    passBox.setPosition({ leftX, 280 + shiftY });

    Text idLabel(font, "ID:", 24), passLabel(font, "PW:", 24);
    idLabel.setPosition({ leftX - 50, 210 + shiftY });
    passLabel.setPosition({ leftX - 50, 290 + shiftY });
    idLabel.setFillColor(Color::White);
    passLabel.setFillColor(Color::White);

    Text idText(font, "", 24), passText(font, "", 24);
    idText.setPosition({ leftX + 10, 210 + shiftY });
    passText.setPosition({ leftX + 10, 290 + shiftY });
    idText.setFillColor(Color::Black);
    passText.setFillColor(Color::Black);

    RectangleShape checkbox(Vector2f(25, 25));
    checkbox.setPosition({ leftX, 335 + shiftY });
    checkbox.setFillColor(Color::White);

    Text checkboxLabel(font, "Show Password", 24);
    checkboxLabel.setPosition({ leftX + 40, 330 + shiftY });
    checkboxLabel.setFillColor(Color::White);

    Text checkMark(font, "V", 24);
    checkMark.setPosition({ leftX + 5, 332 + shiftY });
    checkMark.setFillColor(Color::Black);
    checkMark.setString("");

    RectangleShape cursor(Vector2f(2, 35));
    cursor.setFillColor(Color::Black);
    float cursorTimer = 0.f;
    float cursorBlinkRate = 10.f;
    bool cursorVisible = true;

    while (window.isOpen()) {
        float deltaTime = 1.f / 60.f;

        while (const optional<Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
                return false;
            }

            if (event->is<Event::MouseButtonPressed>()) {
                Vector2f mousePos = Vector2f(Mouse::getPosition(window));
                if (checkbox.getGlobalBounds().contains(mousePos)) {
                    showPassword = !showPassword;
                    passText.setString(showPassword ? password : string(password.size(), '*'));
                    checkMark.setString(showPassword ? "V" : "");
                }
                if (loginButton.getGlobalBounds().contains(mousePos)) {
                    if (db.checkLogin(id, password)) {
                        status.setFillColor(Color::Green);
                        status.setString("Login successful!");
                        userID = id;
                        window.display();
                        this_thread::sleep_for(chrono::seconds(2));
                        return true;
                    }
                    else {
                        status.setFillColor(Color::Red);
                        status.setString("Invalid ID or Password!");
                    }
                }
                else if (signupButton.getGlobalBounds().contains(mousePos)) {
                    showSignupWindow(window, db);
                }

                isIdActive = idBox.getGlobalBounds().contains(mousePos);
                isPassActive = passBox.getGlobalBounds().contains(mousePos);
            }

            if (const auto* textEvent = event->getIf<Event::TextEntered>()) {
                wchar_t c = static_cast<wchar_t>(textEvent->unicode);
                if (isIdActive) {
                    if (c == '\b' && !id.empty()) id.pop_back();
                    else if (isalnum(c)) id += static_cast<char>(c);
                    idText.setString(id);
                }
                else if (isPassActive) {
                    if (c == '\b' && !password.empty()) password.pop_back();
                    else if (isalnum(c)) password += static_cast<char>(c);
                    passText.setString(showPassword ? password : string(password.size(), '*'));
                }
            }

            if (event->is<Event::KeyPressed>()) {
                if (Keyboard::isKeyPressed(Keyboard::Key::Tab)) {
                    isIdActive = !isIdActive;
                    isPassActive = !isPassActive;
                }
            }
        }

        cursorTimer += deltaTime;
        if (cursorTimer >= cursorBlinkRate) {
            cursorVisible = !cursorVisible;
            cursorTimer = 0.f;
        }

        if (cursorVisible && isIdActive) {
            cursor.setPosition({ leftX + 10 + idText.getLocalBounds().size.x , 210 + shiftY });
        }
        else if (cursorVisible && isPassActive) {
            cursor.setPosition({ leftX + 10 + passText.getLocalBounds().size.x, 290 + shiftY });
        }

        window.clear(Color::Black);
        window.draw(background);
        window.draw(idLabel);
        window.draw(passLabel);
        window.draw(idBox);
        window.draw(passBox);
        window.draw(idText);
        window.draw(passText);
        window.draw(loginButton);
        window.draw(signupButton);
        window.draw(status);
        window.draw(checkbox);
        window.draw(checkboxLabel);
        window.draw(checkMark);
        if (cursorVisible) window.draw(cursor);
        window.display();
    }

    return false;
}
