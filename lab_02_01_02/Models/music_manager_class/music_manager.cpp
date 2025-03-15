#include "music_manager.h"
#include "../track_class/track.h"

#include <iostream>
#include <cstring>

void MusicManager::displayAllTracks(){

    if (tracks_count == 0) {
        std::cout << "Нет записей!\n";
        return;
    }

    for (int i = 0; i < tracks_count; i++){
        track_id[i].displayInfoAboutTrack();
    }
}