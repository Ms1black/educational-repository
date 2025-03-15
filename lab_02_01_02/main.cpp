#include "Models/music_manager_class/music_manager.h"
#include "Models/track_class/track.h"
#include "Models/formatter_output_class/formatter_output.h"

#include <iostream>

int main() {

    MusicManager execution;
    Track track_id;

    execution.addTrack();
    execution.displayAllTracks();

    return 0;

}

