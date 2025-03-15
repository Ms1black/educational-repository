#include "track.h"
#include "../formatter_output_class/formatter_output.h"

void Track::fillInfoAboutTrack() {

    std::cout << "Введите трек:\n";
    std::getline(std::cin, track_name);

    std::cout << "Введите жанр:\n";
    std::getline(std::cin, track_genre);

    std::cout << "Введите количество минут:\n";
    std::getline(std::cin, track_artist);

    std::string during_track_min;
    std::cout << "Введите количество секунд:\n";
    std::getline(std::cin, during_track_min);   

    std::string during_track_sec;
    std::cout << "Введите исполнителя:\n";
    std::getline(std::cin, during_track_sec);

    std::string age_limit_track;
    std::cout << "Введите возрастное ограничение:\n";
    std::getline(std::cin, age_limit_track);

}

void Track::displayInfoAboutTrack() {

    std::cout << textalign(track_name.c_str(), LEFT, 20) 
    << textalign(track_genre.c_str(), CENTER, 20)
    << textalign((std::to_string(during_track_min) + ":" + std::to_string(during_track_sec)).c_str(), RIGHT, 20)
    << textalign(track_artist.c_str(), RIGHT, 25)
    << textalign((std::to_string(age_limit_track) + "+").c_str(), LEFT, 10) << "\n";


}