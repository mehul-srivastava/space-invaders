#include <ncurses.h>
#include <iostream>
#include <string>
#include <fstream>

#include "Menu.h"
#include "Game.h"
#include "../exports/Exports.h"

Menu::Menu() { 
  initscr();
  noecho();
  curs_set(0);
  cbreak();
  nodelay(stdscr, false);
  keypad(stdscr, true);

  int maxHeight, maxWidth;
  getmaxyx(stdscr, maxHeight, maxWidth);

  if (maxHeight < 40) {
      endwin();
      std::cerr << "Terminal size is too small. Minimum required height is 40 lines." << std::endl;
      std::exit(1);
  } else if(maxWidth < 190) {
      endwin();
      std::cerr << "Terminal size is too small. Minimum required width is 190 cols." << std::endl;
      std::exit(1);
  }

  int menuY = (maxHeight - menuHeight) / 2;
  int menuX = (maxWidth - menuWidth) / 2;

  menu_window = newwin(menuHeight, menuWidth, menuY, menuX);

  box(menu_window, 0, 0);
  wrefresh(menu_window);
}

void Menu::displayTitle() {
  for (int i = 0; i < 5; i++) {
    mvwprintw(menu_window, i + 1, (menuWidth - 93) / 2, menu_title[i].c_str());
  }
}

int Menu::showAndChooseMenuOptions() {
  std::string menu_choices[] = MENU_CHOICES;
  int choice;
  int highlight = 0;

  while (true) {
    displayTitle();
    box(menu_window, 0, 0);
    int color_pair;

    for (int i = 0; i < sizeof(menu_choices) / sizeof(menu_choices[0]); i++) {
      if(highlight == i) color_pair = A_REVERSE;
      else color_pair = A_DIM;

      int totalWidth = 0;
      for (int idx = 0; idx < i; idx++)
          totalWidth += menu_choices[idx].length() + 25;

      wattron(menu_window, color_pair);
      mvwprintw(menu_window, menuHeight - 2, 3 + totalWidth, menu_choices[i].c_str());
      wattroff(menu_window, color_pair);
    }
    wrefresh(menu_window);
    choice = wgetch(menu_window);


    switch (choice) {
      case 97:
        highlight--;
        if (highlight < 0) highlight = 0;
        break;

      case 100:
        highlight++;
        if (highlight >= 4) highlight = 4;
        break;

      case 10:
        if(highlight == 0) {
          std::string name = getUsername(menuWidth, menuHeight);
          new Game(name);
        } else if(highlight == 1) {
          int maxHeight, maxWidth;
          getmaxyx(stdscr, maxHeight, maxWidth);
          showRules(maxHeight, maxWidth);
        } else if(highlight == 2) {
          int maxHeight, maxWidth;
          getmaxyx(stdscr, maxHeight, maxWidth);
          showCredits(maxHeight, maxWidth);
        } else if(highlight == 3) {
          wclear(menu_window);
          wrefresh(menu_window);
          delwin(menu_window);
        }
        break;
    }
  }
}

void Menu::showRules(int yMax, int xMax) {
  std::vector<std::string> names = CONTRIBUTORS;
    int numNames = names.size();

    refresh();

    int creditsWidth = 120;
    int menuHeight = 5;

    int creditsY = menuHeight - 1;
    int creditsX = (xMax - creditsWidth) / 2;

    int maxNameLength = 0;
    for (const auto& name : names) {
        if (name.length() > maxNameLength) {
          maxNameLength = name.length();
        }
    }
    int nameLines = 0;
    if (maxNameLength > creditsWidth) {
        nameLines = (maxNameLength / creditsWidth) + 1;
    }
    int creditsHeight = numNames + 8 + nameLines;

    WINDOW *rules_window = newwin(creditsHeight, creditsWidth, creditsY, creditsX);
    box(rules_window, 0, 0);
    wrefresh(rules_window);

    std::string line1 = "Players need to control the spaceship to eliminate the enemies.";
    mvwprintw(rules_window, 1, 2, line1.c_str());

    std::string line2 = "* press 'W' to move upwards";
    mvwprintw(rules_window, 2, 2, line2.c_str());

    std::string line3 = "* press 'S' to move downwards";
    mvwprintw(rules_window, 3, 2, line3.c_str());

    std::string line4 = "* press 'A' to move left";
    mvwprintw(rules_window, 4, 2, line4.c_str());

    std::string line5 = "* press 'D' to move right";
    mvwprintw(rules_window, 5, 2, line5.c_str());

    std::string line6 = "* press 'P' power up: spaceship can shoot multiple missiles at the same time (can use 3 times only)";
    mvwprintw(rules_window, 6, 2, line6.c_str());

    std::string line7 = "* press 'ENTER' to shoot missiles";
    mvwprintw(rules_window, 7, 2, line7.c_str());

    std::string line8 = "Enemies come in waves, with each new wave being more difficult than the previous one";
    mvwprintw(rules_window, 9, 2, line8.c_str());

    std::string line9 = "They appear in greater numbers and move at a faster speed.";
    mvwprintw(rules_window, 10, 2, line9.c_str());

    std::string line10 = "Additionally, they have 100 HP and require at least 3 bullets to be defeated.";
    mvwprintw(rules_window, 11, 2, line10.c_str());


    wrefresh(rules_window);

    getch();
    wclear(rules_window);
    wrefresh(rules_window);
    delwin(rules_window);
}

// void Menu::showLeaderboard(int yMax, int xMax) {
//     int leaderboardWidth = 80; 
//     int leaderboardHeight = 20;

//     int menuHeight = 4;

//     int leaderboardY = menuHeight - leaderboardHeight - 1;
//     int leaderboardX = (xMax - leaderboardWidth) / 2;

//     WINDOW* leaderboard_window = newwin(leaderboardHeight, leaderboardWidth, leaderboardY, leaderboardX);
//     box(leaderboard_window, 0, 0);
//     refresh();
//     wrefresh(leaderboard_window);

//     std::ifstream leaderboardFile("../leaderboard.txt");
//     if (leaderboardFile.is_open()) {
//         std::string line;
//         int lineCount = 2;

//         std::string leaderboardLine = "LEADERBOARD";
//         mvwprintw(leaderboard_window, 1, (leaderboardWidth - leaderboardLine.length()) / 2, leaderboardLine.c_str());
//         wrefresh(leaderboard_window);

//         // Read the file line by line and display it in the leaderboard window
//         while (std::getline(leaderboardFile, line) && lineCount <= leaderboardHeight - 2) {
//             mvwprintw(leaderboard_window, lineCount, 1, line.c_str());
//             lineCount++;
//         }

//         leaderboardFile.close();
//     }

//     wrefresh(leaderboard_window);

//     getch();
//     wclear(leaderboard_window);
//     wrefresh(leaderboard_window);
//     delwin(leaderboard_window);
// }

void Menu::showCredits(int yMax, int xMax) {
    std::vector<std::string> names = CONTRIBUTORS;
    int numNames = names.size();

    refresh();

    int creditsWidth = 60;
    int menuHeight = 4;

    int creditsY = menuHeight - 1;
    int creditsX = (xMax - creditsWidth) / 2;

    int maxNameLength = 0;
    for (const auto& name : names) {
        if (name.length() > maxNameLength) {
          maxNameLength = name.length();
        }
    }
    int nameLines = 0;
    if (maxNameLength > creditsWidth) {
        nameLines = (maxNameLength / creditsWidth) + 1;
    }
    int creditsHeight = numNames + 8 + nameLines;

    WINDOW *credits_window = newwin(creditsHeight, creditsWidth, creditsY, creditsX);
    box(credits_window, 0, 0);
    wrefresh(credits_window);

    int startY = (creditsHeight - numNames - 6) / 2;

    std::string creditsLine = "=== CREDITS ===";
    mvwprintw(credits_window, 1, (creditsWidth - creditsLine.length()) / 2, creditsLine.c_str());

    std::string developedLine = "Developed by Group 33";
    mvwprintw(credits_window, startY + 2, (creditsWidth - developedLine.length()) / 2, developedLine.c_str());

    std::string membersLine = "MEMBERS";
    mvwprintw(credits_window, startY + 4, (creditsWidth - membersLine.length()) / 2, membersLine.c_str());

    mvwprintw(credits_window, startY + 5, (creditsWidth - 0) / 2, "");

    for (int i = 0; i < numNames; i++) {
        mvwprintw(credits_window, startY + 6 + i + (nameLines * i), (creditsWidth - names[i].length()) / 2, names[i].c_str());
    }

    wrefresh(credits_window);

    getch();
    wclear(credits_window);
    wrefresh(credits_window);
    delwin(credits_window);
}

std::string Menu::getUsername(int menuWidth, int menuHeight) {
  int containerHeight = 3;
  int containerWidth = menuWidth;
  int containerY =  menuHeight*2 + 2; // Adjust the vertical position
  int containerX = (getmaxx(stdscr) - menuWidth) / 2;

  WINDOW *container = newwin(containerHeight, containerWidth, containerY, containerX);

  box(container, 0, 0); 
  wrefresh(container);

  mvwprintw(container, 1, 2, "Enter your name: ");
  wrefresh(container);

  echo();
  char name [100];

  do {
    wrefresh(container);
    wgetstr(container, name);

    if(std::string(name).length() > 10) {
      mvwprintw(container, 1, 2, "Enter your name again (10 characters only): ");
      wrefresh(container);
      continue;
    } else break;
  } while(true);

  noecho();


  wclear(container);
  wrefresh(container);
  delwin(container);

  return std::string(name);
}