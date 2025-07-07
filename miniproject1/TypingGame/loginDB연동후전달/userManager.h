#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <memory>
#include <mysql/jdbc.h>

class MySQLConnector {
private:
    std::unique_ptr<sql::Connection> conn;

public:
    MySQLConnector();
    ~MySQLConnector();

    bool checkLogin(const std::string& id, const std::string& pw);
    bool registerUser(const std::string& id, const std::string& pw);
};

#endif // USERMANAGER_H
