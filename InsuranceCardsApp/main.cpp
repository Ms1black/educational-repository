#include "include/insurance_manager.h"

#include <iostream>

void displayMenu();

int main() {

    InsuranceManager manager;
    InsuranceCard card;

    int choice;

    while (true) {

        displayMenu();

        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {

            case 1: {
                
                manager.addCard();
                break;
            }
            case 2:

                manager.displayAll();
                break;

            case 3: {
                break;
            }
            case 4:

                manager.displayAll();
                break;

            case 5:

                std::cout << "Выход из программы...\n";
                return 0;
            default:
                std::cout << "Неверный выбор, попробуйте снова.\n";
        }

                
        }


    
}

void displayMenu(){

    std::cout << "Меню:\n";
    std::cout << "1 - Ввести все записи\n";
    std::cout << "2 - Распечатать таблицу\n";
    std::cout << "3 - Найти запись по имени\n";
    std::cout << "4 - сортировка по сумме договора\n";
    std::cout << "5 - Выход\n";
}