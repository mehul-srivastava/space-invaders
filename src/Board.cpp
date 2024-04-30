#include <ncurses.h> // Includes the curses header file
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

#include "Board.h" // Includes the Board header file
#include "../exports/Exports.h" // Includes the Exports header file


// Constructor definition for the Board class with initialization of width, height, and text
Board::Board(): game_text("") { 
    initscr(); // Initializes the curses library and sets up the terminal

    start_color(); // Enables color support in the terminal

    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(COLOR_GREEN, 0, 1000, 0);
    init_color(COLOR_MAGENTA, 1000, 500, 0);
    init_color(COLOR_BLUE, 0, 0, 1000);
    init_color(COLOR_CYAN, 0, 1000, 1000);
    init_color(COLOR_YELLOW, 1000, 1000, 0);
    // All the init_color functions define a color `COLOR_{NAME}` with RGB values (1000, 500, 0)

    init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    // Initializes a color pair with a foreground (2nd param) and a background (3rd param)

    noecho(); // Turns off echoing of characters entered by the user
    cbreak(); // Disables line buffering, allowing characters to be processed immediately
    curs_set(0); // Disables the cursor
    nodelay(stdscr, false); // Allows for multiple keys to be pressed together
    // keypad(stdscr, TRUE); // Enables curses to accept keyboard inputs

    int height, width;
    getmaxyx(stdscr, height, width); // Get the current height, width of the terminal
    

    if (height < 30) {
        endwin(); // End the curses mode and restore the terminal settings        
        std::cerr << "Terminal size is too small. Minimum required height is 30 lines." << std::endl;
        std::exit(1);
    } else if(width < 190) {
        endwin(); // End the curses mode and restore the terminal settings        
        std::cerr << "Terminal size is too small. Minimum required width is 190 cols." << std::endl;
        std::exit(1);
    }

    window = newwin(height, width - 40, 0, 0);  // Creates a new window with the specified height, width, and starting coordinates (1, 1: so that has a little bit of space from the terminal)
    leaderboard_window = newwin(height, 40 - 1, 1, width - 40 + 1); // // Initialize new ncurses window
    stats_window = newwin(height, 40 - 1, height - 12, width - 40 + 1); // // Initialize new ncurses window
}

// Takes a text input and puts it into the member initializer `text` (printing on screen is handled by render function)
void Board::displyText(const char* text) { 
    game_text = text; 
}

Board::~Board() {
    werase(window);
    wrefresh(window);
    delwin(window);

    werase(leaderboard_window);
    wrefresh(leaderboard_window);
    delwin(leaderboard_window);

    werase(stats_window);
    wrefresh(stats_window);
    delwin(stats_window);

    endwin();
}

int Board::score = 0;

int Board::getTerminalHeight() {
    return getmaxy(stdscr);
}

int Board::getTerminalWidth() {
    return getmaxx(stdscr);
}

int Board::getInput() {
    wtimeout(window, 25);
    return wgetch(window);
}

void Board::render(vector<Board::LeaderboardEntry> &leaderboard, int round, int lives, int powerups_left) {
    wclear(window);
    wclear(leaderboard_window);

    box(window, BOARD_RIGHT_LEFT_BORDER, BOARD_TOP_BOTTOM_BORDER);
    box(leaderboard_window, ' ', ' ');


    string leaderboard_title = "Realtime Leaderboard";
    wattron(leaderboard_window, COLOR_PAIR(COLOR_CYAN));
    mvwprintw(leaderboard_window, 1, getmaxx(leaderboard_window) / 2 - leaderboard_title.length() / 2 - 1, leaderboard_title.c_str());
    wattroff(leaderboard_window, COLOR_PAIR(COLOR_CYAN));

    int top_15_count = 0;
    for (int i = 0; i < leaderboard.size(); i++) {
        string strscore = to_string(leaderboard[i].score);
        string f = leaderboard[i].name+" : "+strscore;
        mvwprintw(leaderboard_window, i + 3, 1, f.c_str());
        wrefresh(leaderboard_window);

        if(top_15_count >= 15) break;
    }

    string stats_title = "Game Stats";
    wattron(stats_window, COLOR_PAIR(COLOR_YELLOW));
    mvwprintw(stats_window, 1, getmaxx(leaderboard_window) / 2 - stats_title.length() / 2 - 1, stats_title.c_str());
    wattroff(stats_window, COLOR_PAIR(COLOR_YELLOW));

    string lives_remaining = "Lives: " + to_string(lives) + " remaining";
    mvwprintw(stats_window, 3, 1, lives_remaining.c_str());

    string powerups_remaining = "Powerups: " + to_string(powerups_left) + " remaining";
    mvwprintw(stats_window, 4, 1, powerups_remaining.c_str());

    string wave = "Wave: " + to_string(round);
    mvwprintw(stats_window, 6, 1, wave.c_str());

    string kills = "Kills: " + to_string(score);
    mvwprintw(stats_window, 7, 1, kills.c_str());

    for (int i = 0; i < _objects.size(); i++) {
        Sprite* obj = _objects.at(i);
        int startY = obj->getPosY(), startX = obj->getPosX();
        char* rep = obj->getRep();

        for (int j = i + 1; j < _objects.size(); j++) {
            Sprite* obj2 = _objects.at(j);
            if (obj->getPosX() == obj2->getPosX() && obj->getPosY() == obj2->getPosY()) {
                obj->detectCollision(*obj2);
            }
        }

        if (obj->getIsDestroyed() || obj->getPosX() > getTerminalWidth() || obj->getPosY() > getTerminalHeight() || obj->getPosY() < 0 || obj->getPosX() < 0) {
            _objects.erase(_objects.begin() + i);
            break;
        }

        for (int c = 0; c < 100; c++) {
            if(rep[c] == '\0') break;

            switch(rep[c]) {
                case '\n':
                    startY++;
                    startX = obj->getPosX() - 1;
                    break;

               case '<': case '=': case '(':
               case ')': case '[': case ']':
               case '>': case '/': case '\\':
                    wattron(window, COLOR_PAIR(COLOR_WHITE));
                    mvwaddch(window, startY, startX, '>');
                    wattroff(window, COLOR_PAIR(COLOR_WHITE));
                    break;
                
                case '0':
                    wattron(window, COLOR_PAIR(COLOR_WHITE));
                    mvwaddch(window, startY, startX, rep[c]);
                    wattroff(window, COLOR_PAIR(COLOR_WHITE));
                    break;
                
                case 'A':
                    int pair = obj->getColor();
                    wattron(window, COLOR_PAIR(pair));
                    mvwaddch(window, startY, startX, rep[c]);
                    wattroff(window, COLOR_PAIR(pair));
                    break;
            }
            startX++;
        }
        obj->update();
    }
    wrefresh(window);
    wrefresh(leaderboard_window);
    wrefresh(stats_window);
}

void Board::addObject(Sprite* object) {
    _objects.push_back(object);
}

std::vector<Sprite*> Board::getObjects(string sprite) {
    std::vector<Sprite*> filtered = std::vector<Sprite*>();
    for (int i = 0; i < _objects.size(); i++) {
        if (_objects.at(i)->getRep() == sprite) 
            filtered.push_back(_objects.at(i));
    }
    return filtered;
}

void Board::removeObjects(string sprite) {
    std::vector<Sprite*> filtered = std::vector<Sprite*>();
    for (int i = 0; i < _objects.size(); i++) {
        if (_objects.at(i)->getRep() != sprite) 
            filtered.push_back(_objects.at(i));
    }
    _objects = filtered;
    return;
}

bool Board::compareLeaderboardEntries(const Board::LeaderboardEntry &a, const Board::LeaderboardEntry &b) {
  return a.score > b.score;
}

std::vector<Board::LeaderboardEntry> Board::getLeaderboardEntries(std::string filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<Board::LeaderboardEntry> leaderboard;

    while (std::getline(file, line)) {
      size_t pos = line.find(',');
      if (pos != std::string::npos) {
        std::string name = line.substr(0, pos);
        int score = std::stoi(line.substr(pos + 1));
        Board::LeaderboardEntry entry;
        entry.name = name;
        entry.score = score;
        leaderboard.push_back(entry);
      }
    }
    file.close();

    return leaderboard;
}

void Board::sortLeaderboardEntries(std::vector<Board::LeaderboardEntry>& leaderboard) {
    std::sort(leaderboard.begin(), leaderboard.end(), compareLeaderboardEntries);
    return;
}
