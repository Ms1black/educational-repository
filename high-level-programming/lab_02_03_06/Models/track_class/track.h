#ifndef TRACK_H
#define TRACK_H

#include <iostream>
#include <string>

class Track {
public:
    std::string track_name;
    std::string track_genre;
    std::string artist_name;
    int during_track_min;
    int during_track_sec;
    int age_limit_track;

    friend std::ostream& operator<<(std::ostream& os, const Track& track);
    friend std::istream& operator>>(std::istream& in, Track& track);

};

std::ostream& operator<<(std::ostream& os, const Track& track);

#endif