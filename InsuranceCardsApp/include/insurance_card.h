#ifndef INSURANCE_CARD_H
#define INSURANCE_CARD_H

#include <string>
#include <iostream>

struct InsuranceCard {

    std::string insured_name, agent_name, start_date, end_date, insurance_type, phone_number;
    double contract_amount = 0, discount = 0;

    void fillCard();
    void displayCard() const;

};


#endif