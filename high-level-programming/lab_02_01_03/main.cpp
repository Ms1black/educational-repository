#include "Models/music_manager_class/music_manager.h"
#include "Models/artist_class/artist.h"
#include "tests.h"

#include <iostream>

void showMenu();

int main() {
    MusicManager manager;
    int choice;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                testUploadAlbum(manager);
                break;
            case 2:
                manager.displayAllTracks();
                break;
            case 3:
                std::cout << "Выход из программы...\n";
                break;
            case 4: {
                Track new_track;
                std::cin.ignore();
                std::cin >> new_track;
                manager.addTrack(new_track);
                break;
            }

            case 5:
                manager.displayAllTracks("Хип-хоп");
                break;

            default:
                std::cout << "Неверный ввод! Попробуйте снова.\n";
        }

    } while (choice != 3);

    return 0;
}

void showMenu() {
    std::cout << "\nМеню:\n";
    std::cout << "1. Загрузить тестовый альбом\n";
    std::cout << "2. Показать все треки\n";
    std::cout << "3. Выйти\n";
    std::cout << "4. Добавить трек вручную\n";
    std::cout << "5. Вывести треки жанра хип-хоп\n";
    std::cout << "Выберите действие: ";
}
