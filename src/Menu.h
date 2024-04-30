#ifndef menu_h
#define menu_h

#include <ncurses.h>// Include the ncurses library for terminal-based graphics
#include <string>// Include the string library for using the string data type

using namespace std;

class Menu {
private:
    WINDOW *menu_window;// Pointer to a ncurses window representing the menu
    std::string menu_title[5] = {// Array of strings representing the menu title
    "  ____ ___  ____  __  __ ___ ____   ___ _   _ _____ ____  _   _ ____  _____ ____  ____",
    " / ___/ _ \\/ ___||  \\/  |_ _/ ___| |_ _| \\ | |_   _|  _ \\| | | |  _ \\| ____|  _ \\/ ___|",
    "| |  | | | \\___ \\| |\\/| || | |      | ||  \\| | | | | |_) | | | | | | |  _| | |_) \\___ \\",
    "| |__| |_| |___) | |  | || | |___   | || |\\  | | | |  _  | |_| | |_| | |___|  _ < ___) |",
    " \\____\\___/|____/|_|  |_|___\\____| |___|_| \\_| |_| |_|  \\_\\___/|____/|_____|_| \\_|____/",                                                            
    };
    int menuHeight = 10;// Integer representing the height of the menu
    int menuWidth = 120;// Integer representing the width of the menu

public:
    Menu();// Default constructor for the Menu class
    int showAndChooseMenuOptions(); // Function to show the menu options and allow the user to choose an option
    void displayTitle();// Function to display the menu title
    void showCredits(int yMax, int xMax);// Function to show the credits section of the menu
    void showLeaderboard(int yMax, int xMax);// Function to show the leaderboard section of the menu
    void showRules(int yMax, int xMax);// Function to show the rules section of the menu
    std::string getUsername(int menuWidth, int menuHeight);// Function to get the username from the user
};

#endif
