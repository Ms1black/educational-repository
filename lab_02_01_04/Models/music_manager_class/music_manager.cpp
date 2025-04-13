#include "music_manager.h"
#include "../track_class/track.h"
#include "../formatter_output_class/formatter_output.h"
#include "../vector_class/vector_class.h"

#include <iostream>

MusicManager::MusicManager() {}

void MusicManager::displayAllTracks() {
    if (track_list.size() == 0) {
        std::cout << "\nНет записей!\n\n";
        return;
    }
    std::cout << "\n\U0001F3B5 Список доступных треков:\n\n";
    std::cout << textalign("Трек", LEFT, 30)
              << textalign("Жанр", LEFT, 35)
              << textalign("Исполнитель", LEFT, 30)
              << textalign("Длительность", CENTER, 15)
              << textalign("Возр. огр.", RIGHT, 15) << "\n";

    std::cout << "------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    for (int i = 0; i < track_list.size(); ++i) {
        std::cout << track_list[i];
    }
}

void MusicManager::displayAllTracks(const std::string& genre_filter) {
    for (int i = 0; i < track_list.size(); ++i) {
        if (track_list[i].track_genre == genre_filter) {
            std::cout << track_list[i];
        }
    }
}

void MusicManager::removeTrack(int track_id) {
    if (track_id >= 0 && track_id < track_list.size()) {
        std::cout << "Удаление трека: " << track_list[track_id].track_name << "\n";
        track_list.removeAt(track_id);
    } else {
        std::cout << "Ошибка. Неверный индекс!";
    }
}

void MusicManager::addTrack(const Track& track) {
    track_list.push_back(track);
    std::cout << "\nТрек успешно добавлен в музыкальную коллекцию!\n";
}
