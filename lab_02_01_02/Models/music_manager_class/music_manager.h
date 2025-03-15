#ifndef MANAGER.H
#define MANAGER.H

#include <iostream>
#include <string>
#include "../track.h"

const int TRACKS_COUNT_MAX = 100;

class MusicManager {

    private:

        Track track_id[TRACKS_COUNT_MAX];
        int tracks_count;

    }

    public: 

    MusicManager() : tracks_count(0) {}

    void displayAllTracks();
    void addTrack();


#endif