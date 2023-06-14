#include <iostream>
#include "menu/Menu.h"

int main() {
    auto menu = new Menu();
    menu -> menu();
    delete menu;
}
