#include "track.h"
#include "../formatter_output_class/formatter_output.h"

void Track::fillInfoAboutTrack() {

    std::cout << "Введите трек:\n";
    std::getline(std::cin, track_name);

    std::cout << "Введите жанр:\n";
    std::getline(std::cin, track_genre);

    std::cout << "Введите количество минут:\n";
    std::cin >> during_track_min;   

    std::cout << "Введите количество секунд:\n";
    std::cin >> during_track_sec;

    std::cout << "Введите возрастное ограничение:\n";
    std::cin >> age_limit_track;

    std::cin.ignore();
}

void Track::displayInfoAboutTrack() {

    std::cout << textalign(track_name.c_str(), LEFT, 30) 
    << textalign(track_genre.c_str(), LEFT, 35)
    << textalign(artist_name.c_str(), LEFT, 35)
    << textalign((std::to_string(during_track_min) + ":" + std::to_string(during_track_sec)).c_str(), LEFT, 15)  
    << textalign((std::to_string(age_limit_track) + "+").c_str(), CENTER, 10) << "\n";


}