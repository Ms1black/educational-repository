#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H

#include <iostream>
#include <string>
#include "../track_class/track.h"

const int TRACKS_COUNT_MAX = 100;

class MusicManager {

private:

        Track track_id[TRACKS_COUNT_MAX];
        int tracks_count;

    

    public: 

    MusicManager() : tracks_count(0) {}

    void displayAllTracks();

    void addTrack(){
            
        Track track;

        track.fillInfoAboutTrack();

        if (tracks_count < 100) {
            track_id[tracks_count] = track;
            tracks_count ++;
        } else {
            std:: cout << "Максимальное количество треков достигнуто!" << std::endl;
        }

    }

};


#endif