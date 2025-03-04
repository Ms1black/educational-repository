#ifndef INSURANCE_MANAGER_H
#define INSURANCE_MANAGER_H

#include "insurance_card.h"

class InsuranceManager {

private:

    InsuranceCard cards[100];
    int count;

    void PrintLine() const;
    void PrintTableHeader() const;
public: 

    InsuranceManager() : count(0) {}

    void addCard(const InsuranceManager& card);
    void displayAll() const;

};

#endif