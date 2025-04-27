    #ifndef MUSIC_MANAGER_H
    #define MUSIC_MANAGER_H

    #include <iostream>
    #include <string>
    #include "../track_class/track.h"
    #include "../artist_class/artist.h"

    const int TRACKS_COUNT_MAX = 100;

    class MusicManager {

    private:

            Track track_list[TRACKS_COUNT_MAX];
            int tracks_count;

        

        public: 

        MusicManager();

        void displayAllTracks();
        void addTrack(const Track& track);
        void removeTrack(int track_id);

    };


    #endif