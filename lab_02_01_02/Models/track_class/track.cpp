#include "track.h"
#include "../formatter_output.h"

void Track::fillInfoAboutTrack() {

    std::cout << "Введите трек:\n";
    std::getline(std::cin, track_name);

    std::cout << "Введите жанр:\n";
    std::getline(std::cin, track_genre);

    std::cout << "Введите количество минут:\n";
    std::getline(std::cin, track_artist);

    std::cout << "Введите количество секунд:\n";
    std::getline(std::cin, during_track_min);

    std::cout << "Введите исполнителя:\n";
    std::getline(std::cin, during_track_sec);

    std::cout << "Введите возрастное ограничение:\n";
    std::getline(std::cin, age_limit_track);

}

void Track::displayInfoAboutTrack() {

    std::cout << texalign(track_name.c_str(), LEFT, 20) 
    << textalign(track_genre,c_str(), CENTER, 15)
    << textalign((std::to_string(during_track_min.c_str()) + ":" + std::to_string(during_track_sec)), RIGHT, 20)
    << textalign(track_artist,c_str(), RIGHT, 25)
    << textalign((std::to_string(age_limit_track.c_str())"+")) << "\n";


}