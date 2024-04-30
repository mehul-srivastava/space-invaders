#ifndef game_h
#define game_h

#include <ncurses.h>// Library for creating text-based user interfaces
#include <string>// String operations
#include <vector>// Vector container

#include "Board.h"// User-defined header file for Board class
#include "Spaceship.h"// User-defined header file for Spaceship class


class Game {
public:
    Game(std::string name);// Constructor that takes a string parameter for the player's name
    void run(Board* board, int high_score, std::string name, std::vector<Board::LeaderboardEntry> leaderboard);// Function to run the game
    void updateRound(int& round, Board* board);// Function to update the current round of the game
    void checkSpaceshipDeath(Spaceship* spaceship, Board* board); // Function to check if the spaceship has been destroyed
    void checkSpaceshipPowerups(Spaceship* spaceship, int round);// Function to check for spaceship power-ups based on the current round
    void checkLeaderboardAndUpdate(Board* board, int& high_score, std::vector<Board::LeaderboardEntry>& leaderboard, std::string name);// Function to check the leaderboard and update it if necessary
};

#endif
