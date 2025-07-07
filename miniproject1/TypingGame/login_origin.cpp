//#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Window/Event.hpp>
// 
//#include <fstream>
//#include <unordered_map>
//#include <string>
//#include <iostream>
//#include <chrono>
//#include <thread>
//
//using namespace std;
//using namespace sf;
//using namespace chrono;
//
//const string USERS_FILE = "users.txt";
//
//// 사용자 로드 및 저장 함수
//unordered_map<string, string> loadUsers() {
//    unordered_map<string, string> users;
//    ifstream file(USERS_FILE);
//    string id, password, nickname;
//    while (file >> id >> password >> nickname) {
//        users[id] = password;
//    }
//    return users;
//}
//
//void saveUser(const string& id, const string& password, const string& nickname) {
//    ofstream file(USERS_FILE, ios::app);
//    file << id << " " << password << " " << nickname << endl;
//}
//
//// 회원가입 창 표시 함수
//void showSignupWindow(RenderWindow& window, unordered_map<string, string>& users) {
//    string nickname, id, password;
//    bool isNicknameActive = true, isIdActive = false, isPassActive = false, showPassword = false;
//    Font font;
//    font.openFromFile("assets/fonts/D2Coding.ttf");
//
//    Text title(font, "Sign Up", 30);
//    title.setPosition({ 200, 50 });
//    title.setFillColor(Color::White);
//
//    Text status(font, "", 20);
//    status.setPosition({ 50, 85 });
//    status.setFillColor(Color::Red);
//
//    RectangleShape inputBox(Vector2f(350, 40)); // 입력 박스 크기 조정
//    inputBox.setFillColor(Color::White);
//    inputBox.setOutlineColor(Color::Black);
//    inputBox.setOutlineThickness(2);
//
//    RectangleShape nicknameBox = inputBox, idBox = inputBox, passBox = inputBox;
//    nicknameBox.setPosition({ 100, 120 });
//    idBox.setPosition({ 100, 180 });
//    passBox.setPosition({ 100, 240 });
//
//    Text nicknameLabel(font, "Name:", 20), idLabel(font, "ID:", 20), passLabel(font, "PW:", 20);
//    nicknameLabel.setPosition({ 35, 125 });
//    idLabel.setPosition({ 50, 185 });
//    passLabel.setPosition({ 50, 245 });
//    nicknameLabel.setFillColor(Color::White);
//    idLabel.setFillColor(Color::White);
//    passLabel.setFillColor(Color::White);
//
//    Text nicknameText(font, "", 20), idText(font, "", 20), passText(font, "", 20);
//    nicknameText.setPosition({ 110, 125 });
//    idText.setPosition({ 110, 185 });
//    passText.setPosition({ 110, 245 });
//    nicknameText.setFillColor(Color::Black);
//    idText.setFillColor(Color::Black);
//    passText.setFillColor(Color::Black);
//
//    // 커서 관련 변수
//    RectangleShape cursor(Vector2f(2, 30));  // 커서 크기
//    cursor.setFillColor(Color::Black);
//    float cursorTimer = 0.f;  // 커서 깜빡임 시간
//    float cursorBlinkRate = 10.f;  // 커서 깜빡임 주기 (초)
//    bool cursorVisible = true;  // 커서 가시성 상태
//
//    // 회원가입 버튼
//    RectangleShape signupButton(Vector2f(200, 50));
//    signupButton.setPosition({ 150, 330 });
//    signupButton.setFillColor(Color::Blue);
//
//    Text signupText(font, "Sign Up", 24);
//    signupText.setPosition({ 210, 340 });
//    signupText.setFillColor(Color::White);
//
//    // 비밀번호 표시 체크박스 추가
//    RectangleShape checkbox(Vector2f(20, 20));
//    checkbox.setPosition({ 100, 290 });
//    checkbox.setFillColor(Color::White);
//
//    Text checkboxLabel(font, "Show Password", 20);
//    checkboxLabel.setPosition({ 130, 290 });
//    checkboxLabel.setFillColor(Color::White);
//
//    Text checkMark(font, "V", 20);
//    checkMark.setPosition({ 105, 285 });
//    checkMark.setFillColor(Color::Black);
//    checkMark.setString("");
//
//    RenderWindow signupWindow(VideoMode({ 500, 400 }), "Sign Up");
//
//    while (signupWindow.isOpen()) {
//        float deltaTime = 1.f / 60.f;  // FPS에 맞춘 시간 간격 (60 FPS 가정)
//
//        while (const optional<Event> event = signupWindow.pollEvent()) {
//            if (event->is<Event::Closed>())
//                signupWindow.close();
//
//            if (event->is<Event::MouseButtonPressed>()) {
//                Vector2f mousePos = Vector2f(Mouse::getPosition(signupWindow));
//
//                // 체크박스 클릭
//                if (checkbox.getGlobalBounds().contains(mousePos)) {
//                    showPassword = !showPassword;  // 비밀번호 표시 여부 토글
//                    passText.setString(showPassword ? password : string(password.size(), '*'));
//
//                    // 체크박스 내부에 V 표시 추가/제거
//                    if (showPassword) {
//                        checkMark.setString("V");
//                    }
//                    else {
//                        checkMark.setString("");
//                    }
//                }
//
//                isNicknameActive = nicknameBox.getGlobalBounds().contains(mousePos);
//                isIdActive = idBox.getGlobalBounds().contains(mousePos);
//                isPassActive = passBox.getGlobalBounds().contains(mousePos);
//                if (signupButton.getGlobalBounds().contains(mousePos)) {
//                    saveUser(id, password, nickname);  // 사용자 저장
//                    users[id] = password;  // 메모리 상의 사용자 정보 갱신
//                    status.setFillColor(Color::Green);
//                    status.setString("Sign Up successful! Returning to login...");
//
//                    signupWindow.clear(Color::Black);
//                    signupWindow.draw(title);
//                    signupWindow.draw(nicknameLabel);
//                    signupWindow.draw(idLabel);
//                    signupWindow.draw(passLabel);
//                    signupWindow.draw(nicknameBox);
//                    signupWindow.draw(idBox);
//                    signupWindow.draw(passBox);
//                    signupWindow.draw(nicknameText);
//                    signupWindow.draw(idText);
//                    signupWindow.draw(passText);
//                    signupWindow.draw(signupButton);
//                    signupWindow.draw(signupText);
//                    signupWindow.draw(status);
//                    signupWindow.draw(checkbox);
//                    signupWindow.draw(checkboxLabel);
//                    signupWindow.draw(checkMark);
//                    signupWindow.display();
//
//                    this_thread::sleep_for(chrono::seconds(2));
//                    signupWindow.close();
//                }
//            }
//
//            if (const auto* textEvent = event->getIf<Event::TextEntered>()) {
//                wchar_t c = static_cast<wchar_t>(textEvent->unicode);
//                if (isNicknameActive) {
//                    if (c == '\b' && !nickname.empty()) nickname.pop_back();
//                    else if (isalnum(c) || c == ' ') nickname += static_cast<char>(c);  // 공백도 허용
//                    nicknameText.setString(nickname);
//                }
//                else if (isIdActive) {
//                    if (c == '\b' && !id.empty()) id.pop_back();
//                    else if (isalnum(c)) id += static_cast<char>(c);
//                    idText.setString(id);
//                }
//                else if (isPassActive) {
//                    if (c == '\b' && !password.empty()) password.pop_back();
//                    else if (isalnum(c)) password += static_cast<char>(c);
//                    passText.setString(showPassword ? password : string(password.size(), '*'));
//                }
//            }
//
//            if (event->is<Event::KeyPressed>()) {
//                if (Keyboard::isKeyPressed(Keyboard::Key::Tab)) {
//                    if (isNicknameActive) {
//                        isNicknameActive = false;
//                        isIdActive = true;
//                    }
//                    else if (isIdActive) {
//                        isIdActive = false;
//                        isPassActive = true;
//                    }
//                    else if (isPassActive) {
//                        isPassActive = false;
//                        isNicknameActive = true;
//                    }
//                }
//            }
//        }
//
//        // 커서 깜빡이기
//        cursorTimer += deltaTime;
//        if (cursorTimer >= cursorBlinkRate) {
//            cursorVisible = !cursorVisible;
//            cursorTimer = 0.f;
//        }
//
//        if (cursorVisible && isNicknameActive) {
//            cursor.setPosition({ 110 + nicknameText.getLocalBounds().size.x, 125 });  // 커서 X 위치는 nicknameText의 길이에 따라 결정
//        }
//        else if (cursorVisible && isIdActive) {
//            cursor.setPosition({ 110 + idText.getLocalBounds().size.x, 185 });  // 커서 X 위치는 idText의 길이에 따라 결정
//        }
//        else if (cursorVisible && isPassActive) {
//            cursor.setPosition({ 110 + passText.getLocalBounds().size.x, 245 });  // 커서 X 위치는 passText의 길이에 따라 결정
//        }
//
//        signupWindow.clear(Color::Black);
//        signupWindow.draw(title);
//        signupWindow.draw(nicknameLabel);
//        signupWindow.draw(idLabel);
//        signupWindow.draw(passLabel);
//        signupWindow.draw(nicknameBox);
//        signupWindow.draw(idBox);
//        signupWindow.draw(passBox);
//        signupWindow.draw(nicknameText);
//        signupWindow.draw(idText);
//        signupWindow.draw(passText);
//        signupWindow.draw(signupButton);
//        signupWindow.draw(signupText);
//        signupWindow.draw(status);
//        signupWindow.draw(checkbox);
//        signupWindow.draw(checkboxLabel);
//        signupWindow.draw(checkMark);
//        if (cursorVisible) {
//            signupWindow.draw(cursor);  // 커서 표시
//        }
//        signupWindow.display();
//    }
//}
//
//// 로그인 창 표시 함수
//void showLoginWindow(RenderWindow& window) {
//    unordered_map<string, string> users = loadUsers();
//    string id, password;
//    bool isIdActive = false, isPassActive = false, showPassword = false;
//
//    Font font;
//    font.openFromFile("assets/fonts/D2Coding.ttf");
//
//    Text title(font, "Login", 30);
//    title.setPosition({ 210, 50 });
//    title.setFillColor(Color::White);
//
//    Text status(font, "", 20);
//    status.setPosition({ 140, 370 });
//    status.setFillColor(Color::Red);
//
//    RectangleShape inputBox(Vector2f(350, 40));
//    inputBox.setFillColor(Color::White);
//    inputBox.setOutlineColor(Color::Black);
//    inputBox.setOutlineThickness(2);
//
//    RectangleShape idBox = inputBox, passBox = inputBox;
//    idBox.setPosition({ 100, 120 });
//    passBox.setPosition({ 100, 180 });
//
//    Text idLabel(font, "ID:", 20), passLabel(font, "PW:", 20);
//    idLabel.setPosition({ 50, 125 });
//    passLabel.setPosition({ 50, 185 });
//    idLabel.setFillColor(Color::White);
//    passLabel.setFillColor(Color::White);
//
//    Text idText(font, "", 20), passText(font, "", 20);
//    idText.setPosition({ 110, 125 });
//    passText.setPosition({ 110, 185 });
//    idText.setFillColor(Color::Black);
//    passText.setFillColor(Color::Black);
//
//    RectangleShape loginButton(Vector2f(200, 50));
//    loginButton.setPosition({ 150, 260 });
//    loginButton.setFillColor(Color::Green);
//
//    Text loginText(font, "Login", 24);
//    loginText.setPosition({ 220, 270 });
//    loginText.setFillColor(Color::White);
//
//    RectangleShape signupButton(Vector2f(200, 50));
//    signupButton.setPosition({ 150, 320 });
//    signupButton.setFillColor(Color::Blue);
//
//    Text signupText(font, "Sign Up", 24);
//    signupText.setPosition({ 210, 330 });
//    signupText.setFillColor(Color::White);
//
//    RectangleShape checkbox(Vector2f(20, 20));
//    checkbox.setPosition({ 100, 230 });
//    checkbox.setFillColor(Color::White);
//
//    Text checkboxLabel(font, "Show Password", 20);
//    checkboxLabel.setPosition({ 130, 230 });
//    checkboxLabel.setFillColor(Color::White);
//
//    Text checkMark(font, "V", 20);
//    checkMark.setPosition({ 105, 225 });
//    checkMark.setFillColor(Color::Black);
//    checkMark.setString("");
//
//    // 커서 관련 변수
//    RectangleShape cursor(Vector2f(2, 30));  // 커서 크기
//    cursor.setFillColor(Color::Black);
//    float cursorTimer = 0.f;  // 커서 깜빡임 시간
//    float cursorBlinkRate = 10.f;  // 커서 깜빡임 주기 (초)
//    bool cursorVisible = true;  // 커서 가시성 상태
//
//    RenderWindow loginWindow(VideoMode({ 500, 400 }), "Login");
//
//    while (loginWindow.isOpen()) {
//        float deltaTime = 1.f / 60.f;  // FPS에 맞춘 시간 간격 (60 FPS 가정)
//
//        while (const optional<Event> event = loginWindow.pollEvent()) {
//            if (event->is<Event::Closed>())
//                loginWindow.close();
//
//            if (event->is<Event::MouseButtonPressed>()) {
//                Vector2f mousePos = Vector2f(Mouse::getPosition(loginWindow));
//
//                if (checkbox.getGlobalBounds().contains(mousePos)) {
//                    showPassword = !showPassword;
//                    passText.setString(showPassword ? password : string(password.size(), '*'));
//
//                    if (showPassword) {
//                        checkMark.setString("V");
//                    }
//                    else {
//                        checkMark.setString("");
//                    }
//                }
//
//                if (loginButton.getGlobalBounds().contains(mousePos)) {
//                    if (users.count(id) && users[id] == password) {
//                        status.setFillColor(Color::Green);
//                        status.setString("Login successful! Closing...");
//                        loginWindow.close();
//                    }
//                    else {
//                        status.setString("Invalid ID or password!");
//                    }
//                }
//                else if (signupButton.getGlobalBounds().contains(mousePos)) {
//                    showSignupWindow(loginWindow, users);  // 회원가입 창 열기
//                }
//
//                // ID와 비밀번호 입력란 클릭 여부 확인
//                isIdActive = idBox.getGlobalBounds().contains(mousePos);
//                isPassActive = passBox.getGlobalBounds().contains(mousePos);
//            }
//
//            if (const auto* textEvent = event->getIf<Event::TextEntered>()) {
//                wchar_t c = static_cast<wchar_t>(textEvent->unicode);
//                if (isIdActive) {
//                    if (c == '\b' && !id.empty()) id.pop_back();
//                    else if (isalnum(c)) id += static_cast<char>(c);
//                    idText.setString(id);
//                }
//                else if (isPassActive) {
//                    if (c == '\b' && !password.empty()) password.pop_back();
//                    else if (isalnum(c)) password += static_cast<char>(c);
//                    passText.setString(showPassword ? password : string(password.size(), '*'));
//                }
//            }
//
//            if (event->is<Event::KeyPressed>()) {
//                if (Keyboard::isKeyPressed(Keyboard::Key::Tab)) {
//                    if (isIdActive) {
//                        isIdActive = false;
//                        isPassActive = true;
//                    }
//                    else if (isPassActive) {
//                        isPassActive = false;
//                        isIdActive = true;
//                    }
//                }
//            }
//        }
//
//        // 커서 깜빡이기
//        cursorTimer += deltaTime;
//        if (cursorTimer >= cursorBlinkRate) {
//            cursorVisible = !cursorVisible;
//            cursorTimer = 0.f;
//        }
//
//        // 커서 위치 설정
//        if (cursorVisible && isIdActive) {
//            cursor.setPosition({ 110 + idText.getLocalBounds().size.x, 125 });  // 커서 X 위치는 idText의 길이에 따라 결정
//        }
//        else if (cursorVisible && isPassActive) {
//            cursor.setPosition({ 110 + passText.getLocalBounds().size.x, 185 });  // 커서 X 위치는 passText의 길이에 따라 결정
//        }
//
//        loginWindow.clear(Color::Black);
//        loginWindow.draw(title);
//        loginWindow.draw(idLabel);
//        loginWindow.draw(passLabel);
//        loginWindow.draw(idBox);
//        loginWindow.draw(passBox);
//        loginWindow.draw(idText);
//        loginWindow.draw(passText);
//        loginWindow.draw(loginButton);
//        loginWindow.draw(loginText);
//        loginWindow.draw(signupButton);
//        loginWindow.draw(signupText);
//        loginWindow.draw(status);
//        loginWindow.draw(checkbox);
//        loginWindow.draw(checkboxLabel);
//        loginWindow.draw(checkMark);
//        if (cursorVisible) {
//            loginWindow.draw(cursor);
//        }
//        loginWindow.display();
//    }
//}
//
//// main 함수
//int main() {
//    RenderWindow window(VideoMode({ 500, 400 }), "Login System");
//    showLoginWindow(window);  // 로그인 창 표시
//
//    return 0;
//}
