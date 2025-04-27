#include "music_manager.h"
#include "../track_class/track.h"
#include "../formatter_output_class/formatter_output.h"

#include <iostream>
#include <cstring>

MusicManager::MusicManager() : tracks_count(0) {}

    void MusicManager::displayAllTracks(){

        if (tracks_count == 0) {
            std::cout << "\nНет записей!\n\n";
            return;
        }
        std::cout << "\n🎵 Список доступных треков:\n\n";
        std::cout << textalign("Трек", LEFT, 30) 
        << textalign("Жанр", LEFT, 35)
        << textalign("Исполнитель", LEFT, 30)
        << textalign("Длительность", CENTER, 15)
        << textalign("Возр. огр.", RIGHT, 15) << "\n";

        std::cout << "------------------------------------------------------------------------------------------------------------------------------" << std::endl;

        
        for (int i = 0; i < tracks_count; i++){
            std::cout << track_list[i];
        }
    }

    void MusicManager::displayAllTracks(const std::string& genre_filter) {
        for (int i = 0; i < tracks_count; ++i) {
            if (track_list[i].track_genre == genre_filter) {
                std::cout << track_list[i];
            }
        }
    }


void MusicManager::removeTrack(int track_id){

    if (track_id >= 0 && track_id < tracks_count){
        std::cout << "Удаление трека: " << track_list[track_id].track_name << "\n";
        for (int i = track_id; i < tracks_count - 1; i++){
            track_list[i] = track_list[i + 1];
        }
        tracks_count--;
    } else {
        std::cout << "Ошибка. Неверный индекс!";
    }
}

void MusicManager::addTrack(const Track& track) {
    if (tracks_count < TRACKS_COUNT_MAX) {
        track_list[tracks_count] = track;
        tracks_count ++;
        std::cout << "\nТрек успешно добавлен в музыкальную коллекцию!\n";
    } else {
        std:: cout << "\nМаксимальное количество треков достигнуто!\n\n" << std::endl;
    }
}