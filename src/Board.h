#ifndef board_h
#define board_h

#include "Sprite.h"
#include <ncurses.h>
#include <vector>

using namespace std;

class Board {
private:
    int height; // Height of the board
    int width; // Width of the board
    const char* game_text; // Text messages (if any) to be printed on board
    WINDOW *window; // Initialising the ncurses window object
    WINDOW *leaderboard_window;
    WINDOW *stats_window;
    vector<Sprite*> _objects;



public:
    struct LeaderboardEntry {
        std::string name;
        int score;
    };
    static int score; // Score of the game
    Board(); // Board constructor
    ~Board(); // Board deconstructor
    int getTerminalHeight(); // Get board height
    int getTerminalWidth(); // Get board width
    int getInput(); // Get keyboard input
    void render(vector<Board::LeaderboardEntry> &leaderboard, int round, int lives, int powerups_left); // Render board with objects
    void displyText(const char* text); // Prints text on screen
    vector<Sprite*> getObjects(string sprite);
    void addObject(Sprite* object);
    void removeObjects(string sprite);

    static bool compareLeaderboardEntries(const LeaderboardEntry &a, const LeaderboardEntry &b);
    std::vector<Board::LeaderboardEntry> getLeaderboardEntries(std::string filename);
    void sortLeaderboardEntries(std::vector<Board::LeaderboardEntry>& leaderboard);
};

#endif
