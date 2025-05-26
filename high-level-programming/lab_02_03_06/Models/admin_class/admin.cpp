#include "admin.h"

void Admin::removeTrack(MusicManager& manager, int track_id) {
    manager.removeTrack(track_id);
}

void Admin::generateReport(const MusicManager& manager, const std::string& filename) {
    ReportGenerator::generateTracksReport(manager.getAllTracks(), filename);
}