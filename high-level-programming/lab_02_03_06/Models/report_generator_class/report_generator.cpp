#include "report_generator.h"
#include "../formatter_output_class/formatter_output.h"

void ReportGenerator::generateTracksReport(const MyVector<Track>& tracks, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл для отчета: " << filename << std::endl;
        return;
    }

    outFile << "\nСписок доступных треков:\n\n";
    outFile << textalign("Трек", LEFT, 30)
              << textalign("Жанр", LEFT, 35)
              << textalign("Исполнитель", LEFT, 30)
              << textalign("Длительность", CENTER, 15)
              << textalign("Возр. огр.", RIGHT, 15) << "\n";

    outFile << "------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    for (int i = 0; i < tracks.size(); ++i) {
        std::string secs_str = std::to_string(tracks[i].during_track_sec);
        if (tracks[i].during_track_sec < 10) {
            secs_str = "0" + secs_str;
        }
        std::string duration_str = std::to_string(tracks[i].during_track_min) + ":" + secs_str;

        outFile << textalign(tracks[i].track_name.c_str(), LEFT, 30)
           << textalign(tracks[i].track_genre.c_str(), LEFT, 35)
           << textalign(tracks[i].artist_name.c_str(), LEFT, 30)
           << textalign(duration_str.c_str(), CENTER, 15)
           << textalign((std::to_string(tracks[i].age_limit_track) + "+").c_str(), RIGHT, 15)
           << "\n";
    }

    outFile.close();
    std::cout << "Отчет успешно сгенерирован: " << filename << std::endl;
}