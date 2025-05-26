#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H

#include <string>
#include "../vector_class/vector_class.h"
#include "../track_class/track.h"

class MusicManager {
private:
    MyVector<Track> track_list;

public:
    MusicManager();

    void displayAllTracks();
    void displayAllTracks(const std::string& genre_filter);
    void removeTrack(int track_id);
    void addTrack(const Track& track);
    const MyVector<Track>& getAllTracks() const { return track_list; } // Новый метод для отчетов
    void setTracks(const MyVector<Track>& tracks) { track_list = tracks; } // Новый метод для загрузки состояния
};

#endif