#include "../include/insurance_manager.h"
#include "../include/formatter_output.h"

#include <iostream>
#include <cstring>
#include <fstream>

void InsuranceManager::PrintLine() const {

    std::cout << "\033[1;32m----------------------------------------------------------------------------------------------------------------------------\033[0m\n";
    
}

void InsuranceManager::PrintTableHeader() const {

    PrintLine();

    // std::cout << "\033[1;32m* " << textalign("Застрахованный", CENTER, 29) 
    // << " * " << textalign("Агент", CENTER, 20)
    // << " * " << textalign("Сумма", CENTER, 10)
    // << " * " << textalign("Дата страховки", CENTER, 10)
    // << " * " << textalign("Дата оконч. договора", CENTER, 10)
    // << " * " << textalign("Вид страховки", CENTER, 15)
    // << " * " << textalign("Тел. застрахованного", CENTER, 15)
    // << " * " << textalign("Скидка", CENTER, 8) << " *\033[0m\n";

    // PrintLine();

}

void InsuranceManager::displayAll() const {

    if (card_count == 0){

        std::cout << "Нет записей\n";

        return;
    }

    PrintTableHeader();

    for (int i = 0; i < card_count; i++){

        cards[i].displayCard();

    }
}


void InsuranceManager::saveCardstoTxt() {

    std::ofstream fout("data/database.txt");
    if (!fout) {
        std::cout << "Ошибка при открытии файла для записи.\n";
        return;
    }

    for (int i = 0; i < card_count; i++){

        fout << cards[i].insured_name << " "
        << cards[i].agent_name << " "
        << cards[i].contract_amount << " "
        << cards[i].start_date << " "
        << cards[i].end_date << " "
        << cards[i].insurance_type << " "
        << cards[i].phone_number << " "
        << cards[i].discount << " ";

    }

    fout.close();
    std::cout << "Данные успешно сохранены в текстовый файл.\n";
}


void InsuranceManager::loadFromTxt() {

        std::ifstream fin("data/database.txt");
    if (!fin) {
        std::cout << "\033[1;33mОшибка при открытии файла для чтения.\033[0m\n";
        return;
    }

    card_count = 0;
    
    while (fin >> cards[card_count].insured_name
               >> cards[card_count].agent_name
               >> cards[card_count].contract_amount
               >> cards[card_count].start_date
               >> cards[card_count].end_date
               >> cards[card_count].insurance_type
               >> cards[card_count].phone_number
               >> cards[card_count].discount) {

        ++card_count;


        fin.close();
        std::cout << "Данные успешно загружены из текстового файла.\n";

    }
   
}

