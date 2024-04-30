#ifndef game_h
#define game_h

#include <ncurses.h>
#include <string>
#include <vector>

#include "Board.h"
#include "Spaceship.h"


class Game {
public:
    Game(std::string name);
    void run(Board* board, int high_score, std::string name, std::vector<Board::LeaderboardEntry> leaderboard);
    void updateRound(int& round, Board* board);
    void checkSpaceshipDeath(Spaceship* spaceship, Board* board);
    void checkSpaceshipPowerups(Spaceship* spaceship, int round);
    void checkLeaderboardAndUpdate(Board* board, int& high_score, std::vector<Board::LeaderboardEntry>& leaderboard, std::string name);
};

#endif