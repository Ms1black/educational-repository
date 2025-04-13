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

std::ostream& operator<<(std::ostream& out, const Track& track) {
    out << textalign(track.track_name.c_str(), LEFT, 30)
        << textalign(track.track_genre.c_str(), LEFT, 35)
        << textalign(track.artist_name.c_str(), LEFT, 35)
        << textalign((std::to_string(track.during_track_min) + ":" + std::to_string(track.during_track_sec)).c_str(), LEFT, 15)
        << textalign((std::to_string(track.age_limit_track) + "+").c_str(), CENTER, 10)
        << "\n";
    return out;
}
