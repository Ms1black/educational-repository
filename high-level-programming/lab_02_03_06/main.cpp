#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <stdexcept>
#include <cctype>
#include <locale>

#include "music_manager_class/music_manager.h"
#include "artist_class/artist.h"
#include "admin_class/admin.h"
#include "authentication_class/authentication.h"
#include "data_persistance_class/data_persistance.h"
#include "user_manager_class/user_manager.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

enum ErrorCode {
    SUCCESS = 0,
    ERROR_INVALID_INPUT,
    ERROR_EMPTY_FIELD,
    ERROR_INVALID_VALUE,
    ERROR_LOGIN_TAKEN,
    ERROR_PASSWORD_WEAK,
    ERROR_INVALID_USER_TYPE,
    ERROR_AUTHENTICATION_FAILED,
    ERROR_TRACK_NOT_FOUND,
    ERROR_FILE_OPERATION_FAILED,
    ERROR_INVALID_NAME_FORMAT
};

void printErrorMessage(ErrorCode code, const std::string& additional_info = "") {
    std::cerr << RED << BOLD << "✖ ОШИБКА: " << RESET;
    switch (code) {
        case ERROR_INVALID_INPUT:
            std::cerr << "Некорректный ввод. " << additional_info;
            break;
        case ERROR_EMPTY_FIELD:
            std::cerr << "Поле не может быть пустым. " << additional_info;
            break;
        case ERROR_INVALID_VALUE:
            std::cerr << "Некорректное значение. " << additional_info;
            break;
        case ERROR_LOGIN_TAKEN:
            std::cerr << "Логин уже занят. " << additional_info;
            break;
        case ERROR_PASSWORD_WEAK:
            std::cerr << "Пароль слишком простой или короткий. " << additional_info;
            break;
        case ERROR_INVALID_USER_TYPE:
            std::cerr << "Некорректный тип пользователя. " << additional_info;
            break;
        case ERROR_AUTHENTICATION_FAILED:
            std::cerr << "Вход не выполнен. " << additional_info;
            break;
        case ERROR_TRACK_NOT_FOUND:
            std::cerr << "Трек не найден. " << additional_info;
            break;
        case ERROR_FILE_OPERATION_FAILED:
            std::cerr << "Ошибка файловой операции. " << additional_info;
            break;
        case ERROR_INVALID_NAME_FORMAT:
            std::cerr << "Некорректный формат имени/фамилии. " << additional_info;
            break;
        default:
            std::cerr << "Неизвестная ошибка. " << additional_info;
            break;
    }
    std::cerr << std::endl;
}

ErrorCode saveAllData(MusicManager& musicManager, UserManager& userManager) {
    try {
        DataPersistance::saveTracks(musicManager.getAllTracks(), "tracks.txt");
        DataPersistance::saveUsers(userManager, "users.txt");
        return SUCCESS;
    } catch (const std::exception& e) {
        printErrorMessage(ERROR_FILE_OPERATION_FAILED, e.what());
        return ERROR_FILE_OPERATION_FAILED;
    }
}

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void waitForEnter() {
    std::cout << YELLOW << "\nНажмите Enter для продолжения..." << RESET;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void clearScreen() {
    system("clear || cls");
}

bool isValidName(const std::string& name) {
    if (name.empty()) return false;
    for (char c : name) {
        if (!std::isalpha(c, std::locale()) && !std::isspace(c, std::locale())) {
            return false;
        }
    }
    return true;
}

void displayMainMenu() {
    clearScreen();
    std::cout << CYAN << "┌─────────────────────────────────────────────────────┐\n";
    std::cout << "│" << BOLD << "            МУЗЫКАЛЬНОЕ ПРИЛОЖЕНИЕ BMSTU             │\n";
    std::cout << "├─────────────────────────────────────────────────────┤\n";
    std::cout << "│ " << GREEN << "1." << RESET << CYAN << " Войти                                            │\n";
    std::cout << "│ " << GREEN << "2." << RESET << CYAN << " Зарегистрироваться                               │\n";
    std::cout << "│ " << RED << "3." << RESET << CYAN << " Выйти                                            │\n";
    std::cout << "└─────────────────────────────────────────────────────┘\n";
    std::cout << BOLD << "Выберите опцию: " << RESET;
}

void displayUserMenu(User* currentUser) {
    clearScreen();
    std::cout << CYAN << "┌─────────────────────────────────────────────────────┐\n";
    std::cout << "│" << BOLD << "             МЕНЮ ПОЛЬЗОВАТЕЛЯ (" << currentUser->getUserLogin() << ")           " << RESET << CYAN << "\n";
    std::cout << "├─────────────────────────────────────────────────────┤\n";
    currentUser->displayInfoAboutUser();
    std::cout << CYAN << "│ " << GREEN << "1." << RESET << CYAN << " Просмотреть все треки                           \n";
    std::cout << "│ " << GREEN << "2." << RESET << CYAN << " Просмотреть треки по жанру                         \n";

    if (dynamic_cast<Artist*>(currentUser)) {
        std::cout << "│ " << GREEN << "3." << RESET << CYAN << " Загрузить трек                                   \n";
    } else if (dynamic_cast<Admin*>(currentUser)) {
        std::cout << "│ " << GREEN << "3." << RESET << CYAN << " Удалить трек                                     \n";
        std::cout << "│ " << GREEN << "4." << RESET << CYAN << " Сгенерировать отчет о треках                     \n";
    }
    std::cout << "│ " << RED << "0." << RESET << CYAN << " Выйти из аккаунта                                 \n";
    std::cout << "└─────────────────────────────────────────────────────┘\n";
    std::cout << BOLD << "Выберите опцию: " << RESET;
}

int getIntInput(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            clearInputBuffer();
            printErrorMessage(ERROR_INVALID_INPUT, "Ожидалось число.");
            continue;
        }
        
        clearInputBuffer();
        
        if (value < min || value > max) {
            printErrorMessage(ERROR_INVALID_VALUE, "Значение должно быть от " + std::to_string(min) + " до " + std::to_string(max) + ".");
            continue;
        }
        
        return value;
    }
}

std::string getStringInput(const std::string& prompt, bool checkEmpty = true, bool checkName = false) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        if (checkEmpty && input.empty()) {
            printErrorMessage(ERROR_EMPTY_FIELD, "Поле не может быть пустым.");
            continue;
        }
        
        if (checkName && !isValidName(input)) {
            printErrorMessage(ERROR_INVALID_NAME_FORMAT, "Должны быть только буквы и пробелы.");
            continue;
        }
        
        return input;
    }
}

User* loginUser(UserManager& userManager) {
    while (true) {
        clearScreen();
        std::cout << CYAN << "┌─────────────────────────────────────────────────────┐\n";
        std::cout << "│" << BOLD << "                       ВХОД                          │\n";
        std::cout << "└─────────────────────────────────────────────────────┘\n" << RESET;
        
        std::string login = getStringInput("Введите логин: ");
        std::string password = getStringInput("Введите пароль: ");
        
        User* user = Authentication::login(userManager, login, password);
        if (user) {
            std::cout << GREEN << "\n✓ Добро пожаловать, " << user->getFirstName() << "!" << RESET << std::endl;
            waitForEnter();
            return user;
        }
        
        printErrorMessage(ERROR_AUTHENTICATION_FAILED, "Неверный логин или пароль.");
        waitForEnter();
    }
}

void registerUser(UserManager& userManager, MusicManager& musicManager) {
    while (true) {
        clearScreen();
        std::cout << CYAN << "┌─────────────────────────────────────────────────────┐\n";
        std::cout << "│" << BOLD << "                 РЕГИСТРАЦИЯ                         │\n";
        std::cout << "└─────────────────────────────────────────────────────┘\n" << RESET;
        
        std::string first_name = getStringInput("Введите имя: ", true, true);
        std::string last_name = getStringInput("Введите фамилию: ", true, true);
        int age = getIntInput("Введите возраст: ", 1, 120);
        std::string login = getStringInput("Введите логин: ");
        std::string password = getStringInput("Введите пароль: ");
        
        if (password.length() < 6) {
            printErrorMessage(ERROR_PASSWORD_WEAK, "Пароль должен содержать не менее 6 символов.");
            waitForEnter();
            continue;
        }
        
        std::string user_type = getStringInput("Введите тип пользователя (artist/admin): ");
        if (user_type != "artist" && user_type != "admin") {
            printErrorMessage(ERROR_INVALID_USER_TYPE, "Допустимо 'artist' или 'admin'.");
            waitForEnter();
            continue;
        }
        
        try {
            Authentication::registrate(userManager, first_name, last_name, age, login, password, user_type);
            if (saveAllData(musicManager, userManager) == SUCCESS) {
                std::cout << GREEN << "\n✓ Пользователь '" << login << "' успешно зарегистрирован." << RESET << std::endl;
                waitForEnter();
                return;
            }
        } catch (const std::exception& e) {
            printErrorMessage(ERROR_LOGIN_TAKEN, e.what());
            waitForEnter();
        }
    }
}

void artistMenu(Artist* artist, MusicManager& musicManager) {
    while (true) {
        displayUserMenu(artist);
        int choice = getIntInput("", 0, 3);
        
        switch (choice) {
            case 1:
                clearScreen();
                musicManager.displayAllTracks();
                waitForEnter();
                break;
            case 2: {
                clearScreen();
                std::string genre = getStringInput("Введите жанр для фильтрации: ");
                musicManager.displayAllTracks(genre);
                waitForEnter();
                break;
            }
            case 3: {
                clearScreen();
                std::cout << CYAN << "┌─────────────────────────────────────────────────────┐\n";
                std::cout << "│" << BOLD << "                  ЗАГРУЗКА ТРЕКА                 " << RESET << CYAN << "│\n";
                std::cout << "└─────────────────────────────────────────────────────┘\n" << RESET;
                
                std::string name = getStringInput("Введите название трека: ");
                std::string genre = getStringInput("Введите жанр: ");
                int min = getIntInput("Введите минуты: ", 0, 599);
                int sec = getIntInput("Введите секунды: ", 0, 59);
                int age_limit = getIntInput("Введите возрастное ограничение: ", 0, 18);
                
                artist->uploadTrack(musicManager, name, genre, min, sec, age_limit);
                std::cout << GREEN << "\n✓ Трек '" << name << "' успешно загружен." << RESET << std::endl;
                waitForEnter();
                break;
            }
            case 0:
                return;
        }
    }
}

void adminMenu(Admin* admin, MusicManager& musicManager) {
    while (true) {
        displayUserMenu(admin);
        int choice = getIntInput("", 0, 4);
        
        switch (choice) {
            case 1:
                clearScreen();
                musicManager.displayAllTracks();
                waitForEnter();
                break;
            case 2: {
                clearScreen();
                std::string genre = getStringInput("Введите жанр для фильтрации: ");
                musicManager.displayAllTracks(genre);
                waitForEnter();
                break;
            }
            case 3: {
                clearScreen();
                const MyVector<Track>& tracks = musicManager.getAllTracks();
                if (tracks.size() == 0) {
                    std::cout << "Нет треков для удаления.\n";
                    waitForEnter();
                    break;
                }
                
                musicManager.displayAllTracks();
                int track_num = getIntInput("Введите порядковый номер трека для удаления: ", 1, tracks.size());
                
                admin->removeTrack(musicManager, track_num - 1);
                std::cout << GREEN << "\n✓ Трек успешно удален." << RESET << std::endl;
                waitForEnter();
                break;
            }
            case 4: {
                clearScreen();
                std::string filename = getStringInput("Введите имя файла для отчета: ");
                admin->generateReport(musicManager, filename);
                std::cout << GREEN << "\n✓ Отчет успешно сгенерирован в файле: " << filename << RESET << std::endl;
                waitForEnter();
                break;
            }
            case 0:
                return;
        }
    }
}

int main() {
    
    try {
        std::locale::global(std::locale("ru_RU.UTF-8"));
    } catch (const std::runtime_error& e) {
        std::cerr << "Предупреждение: Не удалось установить локаль ru_RU.UTF-8: " << e.what() << std::endl;
        try {
            std::locale::global(std::locale(""));
        } catch (...) {}
    }

    MusicManager musicManager;
    UserManager userManager;
    User* currentUser = nullptr;

    try {
        musicManager.setTracks(DataPersistance::loadTracks("tracks.txt"));
        MyVector<User*> loadedUsers = DataPersistance::loadUsers("users.txt");
        for (int i = 0; i < loadedUsers.size(); ++i) {
            if (loadedUsers[i] != nullptr) {
                userManager.addUser(loadedUsers[i]);
            }
        }
    } catch (const std::exception& e) {
        printErrorMessage(ERROR_FILE_OPERATION_FAILED, e.what());
        std::cerr << "Приложение будет работать с пустыми данными.\n";
        waitForEnter();
    }

    while (true) {
        if (!currentUser) {
            displayMainMenu();
            int choice = getIntInput("", 1, 3);
            
            switch (choice) {
                case 1:
                    currentUser = loginUser(userManager);
                    break;
                case 2:
                    registerUser(userManager, musicManager);
                    break;
                case 3:
                    if (saveAllData(musicManager, userManager) == SUCCESS) {
                        std::cout << GREEN << "Все данные успешно сохранены." << RESET << std::endl;
                    }
                    std::cout << "До свидания!\n";
                    return 0;
            }
        } else {
            if (Artist* artist = dynamic_cast<Artist*>(currentUser)) {
                artistMenu(artist, musicManager);
                currentUser = nullptr;
            } else if (Admin* admin = dynamic_cast<Admin*>(currentUser)) {
                adminMenu(admin, musicManager);
                currentUser = nullptr;
            }
        }
    }

    return 0;
}