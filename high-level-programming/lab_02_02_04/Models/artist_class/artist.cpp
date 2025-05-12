#include "artist.h"

void Artist::uploadTrack(MusicManager& manager, const std::string& name, const std::string& genre, int min, int sec, int age_limit) {
    
    Track newTrack;
    newTrack.track_name = name;
    newTrack.track_genre = genre;
    newTrack.artist_name = getArtistName();
    newTrack.during_track_min = min;
    newTrack.during_track_sec = sec;
    newTrack.age_limit_track = age_limit;

    manager.addTrack(newTrack);
    std::cout << "Загружен трек: " << name << " от " << getArtistName() << std::endl;
}
