#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {

    protected:

        std::string first_name, last_name, user_login, user_password;
        int user_age;

    public:

        User(const std::string& first_name, const std::string& last_name, int user_age, const std::string& user_login, const std::string& user_password) : first_name(first_name), last_name(last_name), user_age(user_age), user_login(user_login), user_password(user_password) {}

        virtual ~User() {}

        virtual void displayInfoAboutUser()  = 0;
        virtual std::string getUserType() const = 0; 
        std::string getUserLogin() const { return user_login; }
        bool checkPassword(const std::string& password) const { return user_password == password; } 

        std::string getFirstName() const { return first_name; }
        std::string getLastName() const { return last_name; }
        int getUserAge() const { return user_age; }
        std::string getPassword() const { return user_password; }
};


#endif