#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "../vector_class/vector_class.h"
#include "../user_class/user.h"

class UserManager {
private:
    MyVector<User*> users;

public:
    ~UserManager();
    void addUser(User* user);
    const MyVector<User*>& getUsers() const;
    void clearUsers();
    bool isLoginTaken(const std::string& login) const; 
};

#endif 