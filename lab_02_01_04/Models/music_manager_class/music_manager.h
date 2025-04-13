    #ifndef MUSIC_MANAGER_H
    #define MUSIC_MANAGER_H

    #include <iostream>
    #include <string>
    #include "../track_class/track.h"
    #include "../artist_class/artist.h"
    #include "../vector_class/vector_class.h"


    class MusicManager {

    private:

            MyVector<Track> track_list;
            int tracks_count;

        

        public: 

        MusicManager();

        void displayAllTracks();
        void displayAllTracks(const std::string& genre_filter);
        void addTrack(const Track& track);
        void removeTrack(int track_id);

    };


    #endif