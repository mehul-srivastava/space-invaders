#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <fstream>

#include "src/Menu.h"

int main() {
  Menu* menu = new Menu();
  menu->showAndChooseMenuOptions();
  
  return 0;
}