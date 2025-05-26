#include "authentication.h"
#include "../user_manager_class/user_manager.h"
#include <iostream>

User* Authentication::login(UserManager& userManager, const std::string& login, const std::string& password) {
    for (int i = 0; i < userManager.getUsers().size(); ++i) {
        User* user = userManager.getUsers()[i];
        if (user->getUserLogin() == login && user->checkPassword(password)) {
            std::cout << "Авторизация успешна. Добро пожаловать, " << user->getUserLogin() << "!\n";
            return user;
        }
    }
    std::cout << "Ошибка: Неверный логин или пароль.\n";
    return nullptr;
}

void Authentication::registrate(UserManager& userManager, const std::string& first_name, const std::string& last_name, int age, const std::string& login, const std::string& password, const std::string& user_type) {
    for (int i = 0; i < userManager.getUsers().size(); ++i) {
        if (userManager.getUsers()[i]->getUserLogin() == login) {
            std::cout << "Ошибка: Пользователь с таким логином уже существует.\n";
            return;
        }
    }

    if (user_type == "artist") {
        userManager.addUser(new Artist(first_name, last_name, age, login, password));
        std::cout << "Регистрация артиста " << first_name << " " << last_name << " успешна.\n";
    } else if (user_type == "admin") {
        userManager.addUser(new Admin(first_name, last_name, age, login, password));
        std::cout << "Регистрация администратора " << first_name << " " << last_name << " успешна.\n";
    }
    else {
        std::cout << "Ошибка: Неизвестный тип пользователя. Доступные типы: artist, admin.\n";
    }
}