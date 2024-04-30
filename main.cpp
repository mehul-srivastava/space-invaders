#include <iostream>// Input/output stream
#include <ncurses.h>// Library for creating text-based user interfaces
#include <sstream>// String stream operations
#include <ctime>// Date and time functions
#include <cstdlib>  // Standard library functions
#include <fstream> // File input/output operations

#include "src/Menu.h" // User-defined header file for Menu class
int main() {
  Menu* menu = new Menu();  // Create a new Menu object using dynamic memory allocation
  menu->showAndChooseMenuOptions(); // Call the showAndChooseMenuOptions() method of the Menu object
  return 0;
}
