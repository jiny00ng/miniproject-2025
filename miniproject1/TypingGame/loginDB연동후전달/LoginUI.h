#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "userManager.h"

// �α��� â�� ���� �α��� ���� �� true ��ȯ, userID�� ������ �޾ƿ�
bool showLoginWindow(sf::RenderWindow& window, MySQLConnector& db, std::string& userID);

// ȸ������ â ���ο��� ����
void showSignupWindow(sf::RenderWindow& parentWindow, MySQLConnector& db);
