#include "data_persistance.h"
#include <fstream>
#include <sstream>

void DataPersistance::saveTracks(const MyVector<Track>& tracks, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл для сохранения треков: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < tracks.size(); ++i) {
        outFile << tracks[i].track_name << "|"
                << tracks[i].track_genre << "|"
                << tracks[i].artist_name << "|"
                << tracks[i].during_track_min << "|"
                << tracks[i].during_track_sec << "|"
                << tracks[i].age_limit_track << "\n";
    }
    outFile.close();
}

MyVector<Track> DataPersistance::loadTracks(const std::string& filename) {
    MyVector<Track> tracks;
    std::ifstream inFile(filename);
    
    if (!inFile.is_open()) {
        std::cerr << "Файл " << filename << " не найден. Будет создан новый." << std::endl;
        return tracks;
    }

    std::string line;
    int line_num = 0;
    while (std::getline(inFile, line)) {
        line_num++;
        try {
            if (line.empty()) continue;
            
            Track track;
            std::istringstream ss(line);
            std::string field;

            if (!std::getline(ss, field, '|')) throw std::runtime_error("Нет названия трека");
            track.track_name = field;

            if (!std::getline(ss, field, '|')) throw std::runtime_error("Нет жанра");
            track.track_genre = field;


            tracks.push_back(track);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка в строке " << line_num << ": " << e.what() 
                     << "\nСтрока: " << line << std::endl;
        }
    }
    return tracks;
}

void DataPersistance::saveUsers(const UserManager& userManager, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл для сохранения пользователей: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < userManager.getUsers().size(); ++i) {
        User* user = userManager.getUsers()[i];
        outFile << user->getUserType() << "|" 
                << user->getFirstName() << "|"
                << user->getLastName() << "|"
                << user->getUserAge() << "|"
                << user->getUserLogin() << "|"
                << user->getPassword() << "\n";
    }
    outFile.close();
}

MyVector<User*> DataPersistance::loadUsers(const std::string& filename) {
    MyVector<User*> users;
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Предупреждение: Файл пользователей не найден или не может быть открыт: " << filename << std::endl;
        return users;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string segment;

        std::getline(ss, segment, '|');
        std::string user_type = segment;

        std::getline(ss, segment, '|');
        std::string first_name = segment;
        std::getline(ss, segment, '|');
        std::string last_name = segment;
        std::getline(ss, segment, '|');
        int age = std::stoi(segment);
        std::getline(ss, segment, '|');
        std::string login = segment;
        std::getline(ss, segment, '|');
        std::string password = segment;

        if (user_type == "artist") {
            users.push_back(new Artist(first_name, last_name, age, login, password));
        } else if (user_type == "admin") {
            users.push_back(new Admin(first_name, last_name, age, login, password));
        }
    }
    inFile.close();
    std::cout << "Пользователи успешно загружены из " << filename << std::endl;
    return users;
}