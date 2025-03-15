#ifndef TRACK_H
#define TRACK_H

#include <iostream>
#include <string>

struct Track {

    std::string track_name, track_genre, track_artist;
    int during_track_min, during_track_sec, age_limit_track;

    void fillInfoAboutTrack();
    void displayInfoAboutTrack();

    };

#endif