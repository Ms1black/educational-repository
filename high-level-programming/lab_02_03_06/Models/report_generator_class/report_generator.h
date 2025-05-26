#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include <string>
#include <fstream>
#include "../vector_class/vector_class.h"
#include "../track_class/track.h"

class ReportGenerator {
public:
    static void generateTracksReport(const MyVector<Track>& tracks, const std::string& filename);
};

#endif