#include "Menu/menu_class.h"
#include "Menu/menu_item_class.h"


const int ITEMS_NUMBER = 1;


int main() {
    CMenuItem items[ITEMS_NUMBER] {CMenuItem{"check user info", PrintUserInfo}};
    CMenu menu("My console menu", items, ITEMS_NUMBER);
    while (menu.runCommand()) {};
    return 0;
}




