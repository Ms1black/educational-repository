#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>
#include "../vector_class/vector_class.h"
#include "../user_class/user.h"
#include "../artist_class/artist.h"
#include "../admin_class/admin.h"


class UserManager; // Forward declaration

class Authentication {
public:
    static User* login(UserManager& userManager, const std::string& login, const std::string& password);
    static void registrate(UserManager& userManager, const std::string& first_name, const std::string& last_name, int age, const std::string& login, const std::string& password, const std::string& user_type);
};

#endif // AUTHENTICATION_H