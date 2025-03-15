#include "../music_manager.h"

#include <iostream>
#include <cstring>

int i = 0;

    void MusicManager::displayAllTracks(){

        if (tracks_count == 0) {
            std::cout << "Нет записей!\n";
            return;
        }

        for (i; i < tracks_count; i++){
            track_id[i].displayInfoAboutTrack();
        }
    }

    void addTrack(){
        
        for (i, i < tracks_count; i++) {
            
            MusicManager track;

            track.fillInfoAbouttrack();

            if (tracks_count < 100) {
                track_id[tracks_count] = track;
                tracks_count ++;
            } else {
                std:: cout << "Максимальное количество треков достигнуто!" << std::endl;
            }

        }

    }