#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include "../user_class/user.h"
#include "../music_manager_class/music_manager.h"
#include "../report_generator_class/report_generator.h"

class Admin : public User {
public:
    using User::User;

    std::string getUserType() const override { return "admin"; }
    void displayInfoAboutUser() override {
        std::cout << "Администратор: " << first_name << " " << last_name << std::endl;
    }

    void removeTrack(MusicManager& manager, int track_id);
    void generateReport(const MusicManager& manager, const std::string& filename);
};

#endif // ADMIN_H