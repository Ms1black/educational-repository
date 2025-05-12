#include "track.h"
#include "../formatter_output_class/formatter_output.h"


std::istream& operator>>(std::istream& in, Track& track) {
    std::cout << "Введите трек:\n";
    std::getline(in, track.track_name);

    std::cout << "Введите жанр:\n";
    std::getline(in, track.track_genre);

    std::cout << "Введите исполнитель:\n";
    std::getline(in, track.artist_name);

    std::cout << "Введите количество минут:\n";
    in >> track.during_track_min;   

    std::cout << "Введите количество секунд:\n";
    in >> track.during_track_sec;

    std::cout << "Введите возрастное ограничение:\n";
    in >> track.age_limit_track;

    in.ignore(); 
    return in;
}

void Track::display(std::ostream& os) const {
    std::string secs_str = std::to_string(during_track_sec);
    if (during_track_sec < 10) {
        secs_str = "0" + secs_str;
    }
    std::string duration_str = std::to_string(during_track_min) + ":" + secs_str;

    os << textalign(track_name.c_str(), LEFT, 30)
       << textalign(track_genre.c_str(), LEFT, 35)
       << textalign(artist_name.c_str(), LEFT, 30)
       << textalign(duration_str.c_str(), CENTER, 15) 
       << textalign((std::to_string(age_limit_track) + "+").c_str(), RIGHT, 15) 
       << "\n";
}