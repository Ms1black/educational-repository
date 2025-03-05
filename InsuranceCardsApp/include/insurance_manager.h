#ifndef INSURANCE_MANAGER_H
#define INSURANCE_MANAGER_H

#include "insurance_card.h"

class InsuranceManager {

private:

    InsuranceCard cards[100];
    int card_count;

    void PrintLine() const;
    void PrintTableHeader() const;
public: 

    InsuranceManager() : card_count(0) {}

    void displayAll() const;

    void addCard() {

        InsuranceCard card;

        card.fillCard();

        if (card_count < 100) {
            cards[card_count] = card;
            card_count++;
        } else {
            std::cout << "Максимальное количество карт достигнуто!" << std::endl;
        }
    }

};

#endif