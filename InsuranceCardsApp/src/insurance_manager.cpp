#include "../include/insurance_manager.h"
#include "../include/formatter_output.h"

#include <iostream>
#include <cstring>

void InsuranceManager::PrintLine() const {

    std::cout << "\033[1;32m-----------------------------------------------------------------------------\033[0m\n";
    
}

void InsuranceManager::PrintTableHeader() const {

    PrintLine();

    std::cout << "\033[1;32m* " << textalign("Застрахованный", CENTER, 20) 
    << " * " << textalign("Агент", CENTER, 20)
    << " * " << textalign("Сумма", CENTER, 10)
    << " * " << textalign("Дата страховки", CENTER, 10)
    << " * " << textalign("Дата оконч. договора", CENTER, 10)
    << " * " << textalign("Вид страховки", CENTER, 15)
    << " * " << textalign("Тел. застрахованного", CENTER, 15)
    << " * " << textalign("Скидка", CENTER, 8) << " *\033[0m\n";

    PrintLine();

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
