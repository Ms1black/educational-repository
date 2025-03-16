#ifndef ARTIST_H
#define ARTIST_H

#include <string>

#include "../user_class/user.h"
#include "../track_class/track.h"
#include "../music_manager_class/music_manager.h"

class MusicManager;

class Artist : public User {

    public:
        using User::User;

        std::string getArtistName() const { return first_name + " " + last_name; }

        void displayInfoAboutUser() override {
        std::cout << "Исполнитель: " << getArtistName() << std::endl;
        }

        void uploadTrack(MusicManager& manager, const std::string& name, const std::string& genre, int min, int sec, int age_limit);
};


#endif