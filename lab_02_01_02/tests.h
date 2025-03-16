#ifndef TESTS_H
#define TESTS_H

#include "Models/music_manager_class/music_manager.h"
#include "Models/artist_class/artist.h"

#include <iostream>

void testUploadAlbum(MusicManager& manager) {

    Artist artist("Playboi","Carti", 29, "pbc", "pbc2025");

    artist.displayInfoAboutUser();
    artist.uploadTrack(manager, "POP OUT", "Трэп", 3, 15, 16);
    artist.uploadTrack(manager, "CRUSH", "Трэп", 3, 45, 16);
    artist.uploadTrack(manager, "K POP", "Хип-хоп", 4, 0, 16);
    artist.uploadTrack(manager, "EVIL J0RDAN", "Рейдж", 3, 30, 18);
    artist.uploadTrack(manager, "MOJO JOJO", "Рейдж", 3, 10, 18);
    artist.uploadTrack(manager, "PHILLY", "Трэп", 3, 50, 16);
    artist.uploadTrack(manager, "RADAR", "Рейдж", 2, 55, 18);
    artist.uploadTrack(manager, "BACKD00R", "R&B / Хип-хоп", 4, 15, 16);
    artist.uploadTrack(manager, "TOXIC", "Грайм", 3, 35, 16);
    artist.uploadTrack(manager, "MUNYUN", "Рейдж", 3, 50, 18);
    artist.uploadTrack(manager, "CRANK", "Рейдж", 3, 40, 18);
    artist.uploadTrack(manager, "CHARGE DEM HOES A FEE", "Трэп", 3, 55, 16);
    artist.uploadTrack(manager, "GOOD CREDIT", "Хип-хоп", 4, 5, 16);
    artist.uploadTrack(manager, "I SEEEEEE YOU BABY BOI", "Рейдж", 2, 50, 18);
    artist.uploadTrack(manager, "WAKE UP F1LTHY", "Трэп", 3, 45, 16);
    artist.uploadTrack(manager, "JUMPIN", "Хип-хоп", 3, 30, 16);
    artist.uploadTrack(manager, "TRIM", "Трэп", 3, 40, 16);
    artist.uploadTrack(manager, "WE NEED ALL DA VIBES", "Хип-хоп", 4, 0, 16);
    artist.uploadTrack(manager, "OLYMPIAN", "Трэп", 3, 10, 16);
    artist.uploadTrack(manager, "OPM BABI", "Рейдж", 3, 50, 18);
    artist.uploadTrack(manager, "TWIN TRIM", "Трэп", 3, 35, 16);
    artist.uploadTrack(manager, "LIKE WEEZY", "Трэп", 3, 25, 16);
    artist.uploadTrack(manager, "DIS 1 GOT IT", "Рейдж", 3, 55, 18);
    artist.uploadTrack(manager, "WALK", "Рейдж", 3, 45, 18);
    artist.uploadTrack(manager, "HBA", "Рейдж", 4, 10, 18);
    artist.uploadTrack(manager, "OVERLY", "Трэп", 3, 30, 16);
    artist.uploadTrack(manager, "SOUTH ATLANTA BABY", "Трэп", 3, 20, 16);

    std::cout << "\nТест успешно загружен!" << std::endl;

}


#endif 
