#include "music_manager.h"
#include "../track_class/track.h"
#include "../formatter_output_class/formatter_output.h"

#include <iostream>
#include <cstring>

void MusicManager::displayAllTracks(){

    if (tracks_count == 0) {
        std::cout << "Нет записей!\n";
        return;
    }

    std::cout << textalign("Трек", LEFT, 30) 
    << textalign("Жанр", LEFT, 30)
    << textalign("Исполнитель", LEFT, 30)
    << textalign("Длительность", CENTER, 25)
    << textalign("Возр. огр.", RIGHT, 23) << "\n";

    std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;


    for (int i = 0; i < tracks_count; i++){
        track_id[i].displayInfoAboutTrack();
    }
}