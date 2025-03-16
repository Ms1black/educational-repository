#include "music_manager_class/music_manager.h"
#include "artist_class/artist.h"
#include "tests.h"

#include <iostream>

int main() {
    
    MusicManager manager;
    
    testUploadAlbum(manager);

    manager.displayAllTracks();

    return 0;
}

