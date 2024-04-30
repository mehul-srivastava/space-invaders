#include <ncurses.h>
#include <string>
#include <fstream>
#include <cmath>

#include "Game.h"
#include "Board.h"
#include "Spaceship.h"
#include "Enemy.h"
#include "Missile.h"

Game::Game(std::string name) {
  Board* board = new Board();

  std::vector<Board::LeaderboardEntry> leaderboard;
  leaderboard = board->getLeaderboardEntries("./leaderboard.txt");

  board->sortLeaderboardEntries(leaderboard);
  int high_score = 0;
  for (int i = 0; i < leaderboard.size(); i++) {
    if (leaderboard[i].name == name) {
      high_score = leaderboard[i].score;
    }
  }

  srand(time(NULL));
  run(board, high_score, name, leaderboard);
}

void Game::run(Board* board, int high_score, std::string name, std::vector<Board::LeaderboardEntry> leaderboard) {

  int round = 0, cooldown_count = 0;
  int board_width = board->getTerminalWidth(), board_height = board->getTerminalHeight();

  Spaceship* spaceship = new Spaceship(floor(board_width / 2), floor(board_height / 2), board_width, board_height);
  board->addObject(spaceship);

  do {
    updateRound(round, board);

    checkSpaceshipDeath(spaceship, board);

    checkSpaceshipPowerups(spaceship, round);

    checkLeaderboardAndUpdate(board, high_score, leaderboard, name);

    board->render(leaderboard, round, spaceship->getLives(), spaceship->powerups_left);
    int c = board->getInput();

    switch(c) {
      case 'w':
        if(spaceship->getPosY() > 1)
          spaceship->moveUp();
        cooldown_count = 0;
        break;

      case 'a':
        if(spaceship->getPosX() > 0 + 2)
          spaceship->moveLeft();
        cooldown_count = 0;
        break;

      case 's':
        if(spaceship->getPosY() < board_height - 1 - 5) // height - 1 (so it does not touch borders), another -5 because it is height of spaceship
          spaceship->moveDown();
        cooldown_count = 0;
        break;

      case 'd':
        if(spaceship->getPosX() < board_width - 40 - 10 - 1) // -9 because it is width of spaceship, -1 cuz of wall
          spaceship->moveRight();
        cooldown_count = 0;
        break;
      
      case 'p':
        if(spaceship->powerups_left > 0) {
          spaceship->isPowerupActivated = true;
          spaceship->roundDuringPowerupActivation = round;
        }
        break;

      case '\n':
        cooldown_count++;

        if(spaceship->isPowerupActivated && cooldown_count < 10) {
          for(int i = -2; i < 2; i++) {
            Missile* missile = new Missile(true, spaceship->getPosX() + 10, spaceship->getPosY() + 2 + i);
            board->addObject(missile);
          }
        } else if(cooldown_count < 10) {
            Missile* missile = new Missile(true, spaceship->getPosX() + 10, spaceship->getPosY() + 2);
            board->addObject(missile);
            break;
        }
    }
  } while (true);
}


void Game::updateRound(int& round, Board* board) {
  if (board->getObjects(ENEMY_REP).size() == 0) {
    for(int a = 1; a <= round * 2 + 1; a++) {
      int randomYPos = std::max(3, std::min(rand() % board->getTerminalHeight(), board->getTerminalHeight() - 8));
      int randomXPos = rand() % 5 + board->getTerminalWidth() - 40 - 10;
      int velocity = round == 1 ? 1 : 
                    (round > 3) ? 6 : round * 2;

      Enemy* enemy = new Enemy(randomXPos, randomYPos, velocity);
      board->addObject(enemy);
    }
    round++;
  }
}


void Game::checkSpaceshipDeath(Spaceship* spaceship, Board* board) {
  if (spaceship->getLives() < 1) {
    board->~Board();
  } else {
    auto enemies = board->getObjects(ENEMY_REP);
    for (auto& enemy : enemies) {
        if (enemy->getPosX() <= 0 && board->getObjects(ENEMY_REP).size() > 0) {
          spaceship->loseLife();
          board->removeObjects(ENEMY_REP);
        }
    }
  }
}


void Game::checkSpaceshipPowerups(Spaceship* spaceship, int round) {
  if(spaceship->isPowerupActivated && round > spaceship->roundDuringPowerupActivation) {
    spaceship->isPowerupActivated = false;
    spaceship->powerups_left -= 1;
  }
}

void Game::checkLeaderboardAndUpdate(Board* board, int& high_score, std::vector<Board::LeaderboardEntry> &leaderboard, std::string name) {
  if (board->score > high_score) {
      bool b = false;
      for (int i = 0; i < leaderboard.size(); i++) {
        if (leaderboard[i].name == name) {
          if (leaderboard[i].score < board->score) {
            leaderboard[i].score = board->score;
            high_score = board->score;
          }
          b = true;
        }
      }
      if (b == false) {
        Board::LeaderboardEntry entry;
        entry.name = name;
        entry.score = high_score;
        leaderboard.push_back(entry);
      }
      board->sortLeaderboardEntries(leaderboard);

      ofstream outFile;
      outFile.open("./leaderboard.txt");
      if (outFile.is_open()) {
        for (int i = 0; i < leaderboard.size(); i++) {
          outFile << leaderboard[i].name << "," << leaderboard[i].score << endl;
        }
        outFile.close();
      }
    }
}