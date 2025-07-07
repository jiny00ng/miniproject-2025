// SignUpUI.cpp
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

void showSignupWindow(RenderWindow& window, MySQLConnector& db) {
    string nickname, id, password;
    bool isNicknameActive = true, isIdActive = false, isPassActive = false, showPassword = false;
    Font font;
    font.openFromFile("assets/fonts/D2Coding.ttf");

    // 수정: 버튼 이미지 로딩
    Texture signupBtnTex;
    if (!signupBtnTex.loadFromFile("assets/images/signup_button.png")) {
        cerr << "버튼 이미지 로드 실패!" << endl;
        return;
    }
    Sprite signupButton(signupBtnTex);
    signupButton.setScale({ 0.2f, 0.2f });
    signupButton.setPosition({ 190.f, 330.f });

    Text title(font, L"회원가입", 30);
    title.setPosition({ 200, 50 });
    title.setFillColor(Color::White);

    Text status(font, "", 20);
    status.setPosition({ 50, 85 });
    status.setFillColor(Color::Red);

    RectangleShape inputBox(Vector2f(350, 40));
    inputBox.setFillColor(Color::White);
    inputBox.setOutlineColor(Color::Black);
    inputBox.setOutlineThickness(2);

    RectangleShape nicknameBox = inputBox, idBox = inputBox, passBox = inputBox;
    nicknameBox.setPosition({ 100, 120 });
    idBox.setPosition({ 100, 180 });
    passBox.setPosition({ 100, 240 });

    Text nicknameLabel(font, "Name:", 20), idLabel(font, "ID:", 20), passLabel(font, "PW:", 20);
    nicknameLabel.setPosition({ 35, 125 });
    idLabel.setPosition({ 50, 185 });
    passLabel.setPosition({ 50, 245 });
    nicknameLabel.setFillColor(Color::White);
    idLabel.setFillColor(Color::White);
    passLabel.setFillColor(Color::White);

    Text nicknameText(font, "", 20), idText(font, "", 20), passText(font, "", 20);
    nicknameText.setPosition({ 110, 125 });
    idText.setPosition({ 110, 185 });
    passText.setPosition({ 110, 245 });
    nicknameText.setFillColor(Color::Black);
    idText.setFillColor(Color::Black);
    passText.setFillColor(Color::Black);

    RectangleShape cursor(Vector2f(2, 30));
    cursor.setFillColor(Color::Black);
    float cursorTimer = 0.f;
    float cursorBlinkRate = 10.f;
    bool cursorVisible = true;

    RectangleShape checkbox(Vector2f(20, 20));
    checkbox.setPosition({ 100, 290 });
    checkbox.setFillColor(Color::White);

    Text checkboxLabel(font, "Show Password", 20);
    checkboxLabel.setPosition({ 130, 290 });
    checkboxLabel.setFillColor(Color::White);

    Text checkMark(font, "V", 20);
    checkMark.setPosition({ 105, 285 });
    checkMark.setFillColor(Color::Black);
    checkMark.setString("");

    RenderWindow signupWindow(VideoMode({ 500, 400 }), L"회원가입");

    while (signupWindow.isOpen()) {
        float deltaTime = 1.f / 60.f;

        while (const optional<Event> event = signupWindow.pollEvent()) {
            if (event->is<Event::Closed>())
                signupWindow.close();

            if (event->is<Event::MouseButtonPressed>()) {
                Vector2f mousePos = Vector2f(Mouse::getPosition(signupWindow));

                if (checkbox.getGlobalBounds().contains(mousePos)) {
                    showPassword = !showPassword;
                    passText.setString(showPassword ? password : string(password.size(), '*'));
                    checkMark.setString(showPassword ? "V" : "");
                }

                isNicknameActive = nicknameBox.getGlobalBounds().contains(mousePos);
                isIdActive = idBox.getGlobalBounds().contains(mousePos);
                isPassActive = passBox.getGlobalBounds().contains(mousePos);

                if (signupButton.getGlobalBounds().contains(mousePos)) {
                    if (nickname.empty() || id.empty() || password.empty()) {
                        status.setFillColor(Color::Red);
                        status.setString("All fields must be filled!");
                    }
                    else {
                        if (db.registerUser(id, password, nickname)) {
                            status.setFillColor(Color::Green);
                            status.setString("Sign Up successful! Returning to login...");
                            signupWindow.display();
                            this_thread::sleep_for(chrono::seconds(2));
                            signupWindow.close();
                        }
                        else {
                            status.setFillColor(Color::Red);
                            status.setString("ID already exists.");
                        }
                    }
                }
            }

            if (const auto* textEvent = event->getIf<Event::TextEntered>()) {
                wchar_t c = static_cast<wchar_t>(textEvent->unicode);
                if (isNicknameActive) {
                    if (c == '\b' && !nickname.empty()) nickname.pop_back();
                    else if (isalnum(c)) nickname += static_cast<char>(c);
                    nicknameText.setString(nickname);
                }
                else if (isIdActive) {
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
                    if (isNicknameActive) {
                        isNicknameActive = false;
                        isIdActive = true;
                    }
                    else if (isIdActive) {
                        isIdActive = false;
                        isPassActive = true;
                    }
                    else if (isPassActive) {
                        isPassActive = false;
                        isNicknameActive = true;
                    }
                }
            }
        }

        cursorTimer += deltaTime;
        if (cursorTimer >= cursorBlinkRate) {
            cursorVisible = !cursorVisible;
            cursorTimer = 0.f;
        }

        if (cursorVisible && isNicknameActive) {
            cursor.setPosition({ 110 + nicknameText.getLocalBounds().size.x, 125 });
        }
        else if (cursorVisible && isIdActive) {
            cursor.setPosition({ 110 + idText.getLocalBounds().size.x, 185 });
        }
        else if (cursorVisible && isPassActive) {
            cursor.setPosition({ 110 + passText.getLocalBounds().size.x, 245 });
        }

        signupWindow.clear(Color::Black);
        signupWindow.draw(title);
        signupWindow.draw(nicknameLabel);
        signupWindow.draw(idLabel);
        signupWindow.draw(passLabel);
        signupWindow.draw(nicknameBox);
        signupWindow.draw(idBox);
        signupWindow.draw(passBox);
        signupWindow.draw(nicknameText);
        signupWindow.draw(idText);
        signupWindow.draw(passText);
        signupWindow.draw(signupButton);
        signupWindow.draw(status);
        signupWindow.draw(checkbox);
        signupWindow.draw(checkboxLabel);
        signupWindow.draw(checkMark);
        if (cursorVisible) {
            signupWindow.draw(cursor);
        }
        signupWindow.display();
    }
}