/////*  SFML 설치 확인 */
////#include <SFML/Graphics.hpp>
////
////int main() {
////    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");
////
////    while (window.isOpen()) {
////        sf::Event event;
////        while (window.pollEvent(event)) {
////            if (event.type == sf::Event::Closed)
////                window.close();
////        }
////
////        window.clear(sf::Color::Blue);
////        window.display();
////    }
////
////    return 0;
////}
//
//
//
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <vector>
//#include <string>
//#include <ctime>
//#include <cstdlib>
//#include <fstream>
//
//// Function to load sentences from a file
//std::vector<std::string> loadSentences(const std::string& filename) {
//    std::vector<std::string> sentences;
//    std::ifstream file(filename);
//
//    if (file.is_open()) {
//        std::string line;
//        while (std::getline(file, line)) {
//            sentences.push_back(line);
//        }
//        file.close();
//    }
//    else {
//        std::cout << "파일을 열 수 없습니다." << std::endl;
//    }
//
//    return sentences;
//}
//
//int main() {
//    srand(static_cast<unsigned int>(time(0)));
//
//    // Load sentences from file
//    std::vector<std::string> sentences = loadSentences("aegukga.txt");
//
//    if (sentences.empty()) {
//        std::cout << "파일에 문장이 없습니다!" << std::endl;
//        return 1;
//    }
//
//    // Create an SFML window
//    sf::RenderWindow window(sf::VideoMode(800, 600), L"타자 연습 게임");
//    window.setFramerateLimit(60);
//
//    // Load font
//    sf::Font font;
//    if (!font.openFromFile("assets/fonts/d2coding.ttf")) {
//        std::cout << L"폰트 파일을 로드할 수 없습니다." << std::endl;
//        return 1;
//    }
//
//    // Create a text object
//    sf::Text text;
//    text.setFont(font);
//    text.setString(" 한글임");  // Example text to display
//    text.setCharacterSize(24);
//    text.setFillColor(sf::Color::White);
//    text.setPosition(200.f, 200.f);
//
//    // Main loop
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//
//        // Clear the window and draw the text
//        window.clear();
//        window.draw(text);
//        window.display();
//    }
//
//    return 0;
//}
