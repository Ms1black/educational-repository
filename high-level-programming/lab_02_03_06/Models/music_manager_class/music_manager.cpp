#include "music_manager.h"
#include "../track_class/track.h"
#include "../formatter_output_class/formatter_output.h"
#include "../vector_class/vector_class.h"

#include <iostream>

MusicManager::MusicManager() {}

void MusicManager::displayAllTracks()
{
    if (track_list.size() == 0)
    {
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

    for (int i = 0; i < track_list.size(); ++i)
    {
        std::cout << track_list[i];
    }
}

void MusicManager::displayAllTracks(const std::string &genre_filter)
{

        std::cout << "\nОтладка: всего треков в памяти - " << track_list.size() << std::endl;

        if (track_list.size() == 0)
        {
            std::cout << "Нет треков для отображения\n";
            return;
        }

        try
        {
            auto &first_track = track_list[0];
            std::cout << "Первый трек в списке: " << first_track.track_name << std::endl;
        }
        catch (...)
        {
            std::cout << "Ошибка доступа к первому треку!\n";
            return;
        }

        bool found = false;
        std::cout << "\n\U0001F3B5 Список треков по жанру '" << genre_filter << "':\n\n";
        std::cout << textalign("Трек", LEFT, 30)
                  << textalign("Жанр", LEFT, 35)
                  << textalign("Исполнитель", LEFT, 30)
                  << textalign("Длительность", CENTER, 15)
                  << textalign("Возр. огр.", RIGHT, 15) << "\n";
        std::cout << "------------------------------------------------------------------------------------------------------------------------------" << std::endl;

        for (int i = 0; i < track_list.size(); ++i)
        {
            if (track_list[i].track_genre == genre_filter)
            {
                std::cout << track_list[i];
                found = true;
            }
        }
        if (!found)
        {
            std::cout << textalign("Нет треков в этом жанре.", LEFT, 125) << "\n";
        }
    }

    void MusicManager::removeTrack(int track_id)
    {
        if (track_id >= 0 && track_id < track_list.size())
        {
            std::cout << "Удаление трека: " << track_list[track_id].track_name << "\n";
            track_list.removeAt(track_id);
            std::cout << "Трек успешно удален.\n";
        }
        else
        {
            std::cout << "Ошибка. Неверный индекс трека!\n";
        }
    }

    void MusicManager::addTrack(const Track &track)
    {
        track_list.push_back(track);
        std::cout << "\nТрек успешно добавлен в музыкальную коллекцию!\n";
    }