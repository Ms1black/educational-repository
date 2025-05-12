#ifndef TRACK_H
#define TRACK_H

#include <iostream>
#include <string>
#include "../../Interfaces/IDisplayable.h"

class Track : public IDisplayable {
public:
    std::string track_name, track_genre;
    std::string artist_name;
    int during_track_min, during_track_sec, age_limit_track;

    Track() : during_track_min(0), during_track_sec(0), age_limit_track(0) {}

    void display(std::ostream& os) const override;
    
    friend std::istream& operator>>(std::istream& in, Track& track);

    };

#endif