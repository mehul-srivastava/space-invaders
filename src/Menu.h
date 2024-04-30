#ifndef menu_h
#define menu_h

#include <ncurses.h>
#include <string>

using namespace std;

class Menu {
private:
    WINDOW *menu_window;
    std::string menu_title[5] = {
    "  ____ ___  ____  __  __ ___ ____   ___ _   _ _____ ____  _   _ ____  _____ ____  ____",
    " / ___/ _ \\/ ___||  \\/  |_ _/ ___| |_ _| \\ | |_   _|  _ \\| | | |  _ \\| ____|  _ \\/ ___|",
    "| |  | | | \\___ \\| |\\/| || | |      | ||  \\| | | | | |_) | | | | | | |  _| | |_) \\___ \\",
    "| |__| |_| |___) | |  | || | |___   | || |\\  | | | |  _  | |_| | |_| | |___|  _ < ___) |",
    " \\____\\___/|____/|_|  |_|___\\____| |___|_| \\_| |_| |_|  \\_\\___/|____/|_____|_| \\_|____/",                                                            
    };
    int menuHeight = 10;
    int menuWidth = 120;

public:
    Menu();
    int showAndChooseMenuOptions();
    void displayTitle();
    void showCredits(int yMax, int xMax);
    void showLeaderboard(int yMax, int xMax);
    void showRules(int yMax, int xMax);
    std::string getUsername(int menuWidth, int menuHeight);
};

#endif