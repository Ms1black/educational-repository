#ifndef DATA_PERSISTANCE_H
#define DATA_PERSISTANCE_H

#include <string>
#include "../vector_class/vector_class.h"
#include "../track_class/track.h"
#include "../user_class/user.h"
#include "../artist_class/artist.h"
#include "../admin_class/admin.h"
#include "../music_manager_class/music_manager.h"
#include "../user_manager_class/user_manager.h"

class DataPersistance {
public:
    static void saveTracks(const MyVector<Track>& tracks, const std::string& filename);
    static MyVector<Track> loadTracks(const std::string& filename);
    static void saveUsers(const UserManager& userManager, const std::string& filename);
    static MyVector<User*> loadUsers(const std::string& filename);
};

#endif 