#ifndef TRACK_H
#define TRACK_H

#include <iostream>
#include <string>

struct Track {

    std::string track_name, track_genre;
    std::string artist_name;
    int during_track_min, during_track_sec, age_limit_track;

    friend std::istream& operator>>(std::istream& in, Track& track);
    friend std::ostream& operator<<(std::ostream& out, const Track& track);


    };

#endif