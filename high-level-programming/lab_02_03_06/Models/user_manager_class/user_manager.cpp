#include "user_manager.h"

UserManager::~UserManager() {
    clearUsers();
}

void UserManager::addUser(User* user) {
    users.push_back(user);
}

const MyVector<User*>& UserManager::getUsers() const {
    return users;
}

void UserManager::clearUsers() {
    for (int i = 0; i < users.size(); ++i) {
        delete users[i];
    }
    users.clear();
}