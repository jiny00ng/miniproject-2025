#include "userManager.h"
#include <iostream>

#define SERVER_IP   "tcp://210.119.12.60:3306"
#define USERNAME    "root"
#define PASSWORD    "1234"
#define DATABASE    "teamDB"

MySQLConnector::MySQLConnector() {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        conn = std::unique_ptr<sql::Connection>(driver->connect(SERVER_IP, USERNAME, PASSWORD));
        conn->setSchema(DATABASE);
        std::cout << "MySQL 연결 성공!" << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cerr << "MySQL 연결 실패: " << e.what() << std::endl;
    }
}

MySQLConnector::~MySQLConnector() {
    std::cout << "MySQL 연결 종료!" << std::endl;
}

bool MySQLConnector::checkLogin(const std::string& id, const std::string& pw) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "SELECT password FROM users WHERE user_id = ?"));
        pstmt->setString(1, id);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            return res->getString("password") == pw;
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "로그인 오류: " << e.what() << std::endl;
    }
    return false;
}

bool MySQLConnector::registerUser(const std::string& id, const std::string& pw) {
    try {
        std::unique_ptr<sql::PreparedStatement> checkStmt(conn->prepareStatement(
            "SELECT COUNT(*) FROM users WHERE user_id = ?"));
        checkStmt->setString(1, id);
        std::unique_ptr<sql::ResultSet> res(checkStmt->executeQuery());
        if (res->next() && res->getInt(1) > 0) return false; // 이미 존재

        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "INSERT INTO users(user_id, password, nickname, profile_img_id) VALUES (?, ?, ?, ?)"));
        pstmt->setString(1, id);
        pstmt->setString(2, pw);
        pstmt->setString(3, "test");
        pstmt->setString(4, "test_profile");  // not null이라 테스트용 임시 설정했슴
        pstmt->execute();
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "회원가입 오류: " << e.what() << std::endl;
    }
    return false;
}
