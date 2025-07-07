// loginUI.cpp
#include "userManager.h"
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
    string id, password;
    bool isIdActive = true, isPassActive = false, showPassword = false;
    Font font;
    font.openFromFile("D2Coding.ttf");

    Text title(font, "Sign Up", 30);
    title.setPosition({ 200, 50 });
    title.setFillColor(Color::White);

    Text status(font, "", 20);
    status.setPosition({ 50, 350 });
    status.setFillColor(Color::Red);

    RectangleShape inputBox(Vector2f(350, 40));
    inputBox.setFillColor(Color::White);
    inputBox.setOutlineColor(Color::Black);
    inputBox.setOutlineThickness(2);

    RectangleShape idBox = inputBox, passBox = inputBox;
    idBox.setPosition({ 100, 120 });
    passBox.setPosition({ 100, 180 });

    Text idLabel(font, "ID:", 20), passLabel(font, "PW:", 20);
    idLabel.setPosition({ 50, 125 });
    passLabel.setPosition({ 50, 185 });
    idLabel.setFillColor(Color::White);
    passLabel.setFillColor(Color::White);

    Text idText(font, "", 20), passText(font, "", 20);
    idText.setPosition({ 110, 125 });
    passText.setPosition({ 110, 185 });
    idText.setFillColor(Color::Black);
    passText.setFillColor(Color::Black);

    RectangleShape cursor(Vector2f(2, 30));
    cursor.setFillColor(Color::Black);
    float cursorTimer = 0.f;
    float cursorBlinkRate = 10.f;
    bool cursorVisible = true;

    RectangleShape signupButton(Vector2f(200, 50));
    signupButton.setPosition({ 150, 290 });
    signupButton.setFillColor(Color::Blue);

    Text signupText(font, "Sign Up", 24);
    signupText.setPosition({ 210, 300 });
    signupText.setFillColor(Color::White);

    RectangleShape checkbox(Vector2f(20, 20));
    checkbox.setPosition({ 100, 230 });
    checkbox.setFillColor(Color::White);

    Text checkboxLabel(font, "Show Password", 20);
    checkboxLabel.setPosition({ 130, 230 });
    checkboxLabel.setFillColor(Color::White);

    Text checkMark(font, "V", 20);
    checkMark.setPosition({ 105, 225 });
    checkMark.setFillColor(Color::Black);
    checkMark.setString("");

    RenderWindow signupWindow(VideoMode({ 500, 400 }), "Sign Up");

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

                isIdActive = idBox.getGlobalBounds().contains(mousePos);
                isPassActive = passBox.getGlobalBounds().contains(mousePos);
                if (signupButton.getGlobalBounds().contains(mousePos)) {
                    if (db.registerUser(id, password)) {
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

            if (event->is<Event::KeyPressed>() && Keyboard::isKeyPressed(Keyboard::Key::Tab)) {
                isIdActive = !isIdActive;
                isPassActive = !isIdActive;
            }
        }

        cursorTimer += deltaTime;
        if (cursorTimer >= cursorBlinkRate) {
            cursorVisible = !cursorVisible;
            cursorTimer = 0.f;
        }
        if (cursorVisible && isIdActive) {
            cursor.setPosition({ 110 + idText.getLocalBounds().size.x, 125 });
        }
        else if (cursorVisible && isPassActive) {
            cursor.setPosition({ 110 + passText.getLocalBounds().size.x, 185 });
        }

        signupWindow.clear(Color::Black);
        signupWindow.draw(title);
        signupWindow.draw(idLabel);
        signupWindow.draw(passLabel);
        signupWindow.draw(idBox);
        signupWindow.draw(passBox);
        signupWindow.draw(idText);
        signupWindow.draw(passText);
        signupWindow.draw(signupButton);
        signupWindow.draw(signupText);
        signupWindow.draw(status);
        signupWindow.draw(checkbox);
        signupWindow.draw(checkboxLabel);
        signupWindow.draw(checkMark);
        if (cursorVisible) signupWindow.draw(cursor);
        signupWindow.display();
    }
}

bool showLoginWindow(RenderWindow& window, MySQLConnector& db, std::string& userID) {
    string id, password;
    bool isIdActive = false, isPassActive = false, showPassword = false;

    Font font;
    font.openFromFile("D2Coding.ttf");

    Text title(font, "Login", 30);
    title.setPosition({ 210, 50 });
    title.setFillColor(Color::White);

    Text status(font, "", 20);
    status.setPosition({ 50, 350 });
    status.setFillColor(Color::Red);

    RectangleShape inputBox(Vector2f(350, 40));
    inputBox.setFillColor(Color::White);
    inputBox.setOutlineColor(Color::Black);
    inputBox.setOutlineThickness(2);

    RectangleShape idBox = inputBox, passBox = inputBox;
    idBox.setPosition({ 100, 120 });
    passBox.setPosition({ 100, 180 });

    Text idLabel(font, "ID:", 20), passLabel(font, "PW:", 20);
    idLabel.setPosition({ 50, 125 });
    passLabel.setPosition({ 50, 185 });
    idLabel.setFillColor(Color::White);
    passLabel.setFillColor(Color::White);

    Text idText(font, "", 20), passText(font, "", 20);
    idText.setPosition({ 110, 125 });
    passText.setPosition({ 110, 185 });
    idText.setFillColor(Color::Black);
    passText.setFillColor(Color::Black);

    RectangleShape loginButton(Vector2f(200, 50));
    loginButton.setPosition({ 150, 260 });
    loginButton.setFillColor(Color::Green);

    Text loginText(font, "Login", 24);
    loginText.setPosition({ 220, 270 });
    loginText.setFillColor(Color::White);

    RectangleShape signupButton(Vector2f(200, 50));
    signupButton.setPosition({ 150, 320 });
    signupButton.setFillColor(Color::Blue);

    Text signupText(font, "Sign Up", 24);
    signupText.setPosition({ 210, 330 });
    signupText.setFillColor(Color::White);

    RectangleShape checkbox(Vector2f(20, 20));
    checkbox.setPosition({ 100, 230 });
    checkbox.setFillColor(Color::White);

    Text checkboxLabel(font, "Show Password", 20);
    checkboxLabel.setPosition({ 130, 230 });
    checkboxLabel.setFillColor(Color::White);

    Text checkMark(font, "V", 20);
    checkMark.setPosition({ 105, 225 });
    checkMark.setFillColor(Color::Black);
    checkMark.setString("");

    RectangleShape cursor(Vector2f(2, 30));
    cursor.setFillColor(Color::Black);
    float cursorTimer = 0.f;
    float cursorBlinkRate = 10.f;
    bool cursorVisible = true;

    RenderWindow loginWindow(VideoMode({ 500, 400 }), "Login");

    while (loginWindow.isOpen()) {
        float deltaTime = 1.f / 60.f;

        while (const optional<Event> event = loginWindow.pollEvent()) {
            if (event->is<Event::Closed>())
                loginWindow.close();

            if (event->is<Event::MouseButtonPressed>()) {
                Vector2f mousePos = Vector2f(Mouse::getPosition(loginWindow));
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
                        loginWindow.display();
                        this_thread::sleep_for(chrono::seconds(1));
                        loginWindow.close();
                        return true;
                    }
                    else {
                        status.setFillColor(Color::Red);
                        status.setString("Invalid ID or Password!");
                    }
                }
                else if (signupButton.getGlobalBounds().contains(mousePos)) {
                    showSignupWindow(loginWindow, db);
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

            if (event->is<Event::KeyPressed>() && Keyboard::isKeyPressed(Keyboard::Key::Tab)) {
                isIdActive = !isIdActive;
                isPassActive = !isIdActive;
            }
        }

        cursorTimer += deltaTime;
        if (cursorTimer >= cursorBlinkRate) {
            cursorVisible = !cursorVisible;
            cursorTimer = 0.f;
        }

        if (cursorVisible && isIdActive) {
            cursor.setPosition({ 110 + idText.getLocalBounds().size.x, 125 });
        }
        else if (cursorVisible && isPassActive) {
            cursor.setPosition({ 110 + passText.getLocalBounds().size.x, 185 });
        }

        loginWindow.clear(Color::Black);
        loginWindow.draw(title);
        loginWindow.draw(idLabel);
        loginWindow.draw(passLabel);
        loginWindow.draw(idBox);
        loginWindow.draw(passBox);
        loginWindow.draw(idText);
        loginWindow.draw(passText);
        loginWindow.draw(loginButton);
        loginWindow.draw(loginText);
        loginWindow.draw(signupButton);
        loginWindow.draw(signupText);
        loginWindow.draw(status);
        loginWindow.draw(checkbox);
        loginWindow.draw(checkboxLabel);
        loginWindow.draw(checkMark);
        if (cursorVisible) loginWindow.draw(cursor);
        loginWindow.display();
    }

    return false;
}