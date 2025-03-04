#include "../include/insurance_card.h"
#include "../include/formatter_output.h"

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