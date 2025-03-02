#include "./CMenu.h"

CMenu::CMenu(string title, CMenuItem *items, size_t count) : title(title), items(items), count(count) {}

int CMenu::getSelect() const {
    return select;
}

bool CMenu::isRun() const {
    return running;
}

size_t CMenu::getCount() const {
    return count;
}

string CMenu::getTitle() {
    return title;
}

CMenuItem *CMenu::getItems() {
    return items;
}

void CMenu::print() {
    for (size_t i{}; i < count; ++i) {
        std::cout << i + 1 << ". ";
        items[i].print();
        std::cout << std::endl;
    }
    std::cout << "0. exit" << std::endl;
}

int CMenu::runCommand() {
    print();
    system("clear");
    std::cout << "\n   Выбор>> ";
    std::cin >> select;
    return (select > 0) ? items[select - 1].run() : 0;
}