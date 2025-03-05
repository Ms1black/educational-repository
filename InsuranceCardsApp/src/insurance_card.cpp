#include "../include/insurance_card.h"
#include "../include/formatter_output.h"
#include "../include/formatter_input.h"


void InsuranceCard::fillCard() {
    
    std::cout << "Введите ФИО застрахованного: ";
    std::getline(std::cin, insured_name);

    std::cout << "Введите ФИО агента: ";
    std::getline(std::cin, agent_name);

    std::string contract_amount_str;

    std::cout << "Введите сумму договора: ";
    std::getline(std::cin, contract_amount_str);
    contract_amount = std::stod(contract_amount_str);

    std::string discount_str;

    std::cout << "Введите скидку: ";
    std::getline(std::cin, discount_str);
    discount = std::stod(discount_str);

    std::cout << "Введите дату начала: ";
    std::getline(std::cin, start_date);

    std::cout << "Введите дату окончания: ";
    std::getline(std::cin, end_date);

    std::cout << "Введите тип страховки: ";
    std::getline(std::cin, insurance_type);

    std::cout << "Введите телефонный номер: ";
    std::getline(std::cin, phone_number);
}

void InsuranceCard::displayCard() const {

    std::cout << "\033[1;32m*\033[0m " << textalign(insured_name.c_str(), LEFT, 20)
    << "\033[1;32m*\033[0m " << textalign(agent_name.c_str(), LEFT, 20)
    << "\033[1;32m*\033[0m " << textalign(std::to_string(contract_amount).c_str(), RIGHT, 10)
    << "\033[1;32m*\033[0m " << textalign(start_date.c_str(), CENTER, 10)
    << "\033[1;32m*\033[0m " << textalign(end_date.c_str(), CENTER, 10)
    << "\033[1;32m*\033[0m " << textalign(insurance_type.c_str(), LEFT, 15)
    << "\033[1;32m*\033[0m " << textalign(phone_number.c_str(), LEFT, 15)
    << "\033[1;32m*\033[0m " << textalign((std::to_string((int)discount) + "%").c_str(), RIGHT, 8)
    << "\033[1;32m*\033[0m\n";
   
}
