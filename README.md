## Team Members
1.	Srivastava Mehul (3036184228)
2.	Shoaib Ibrahim (3036223438)
3.	Poon Tsz Hin (3036224626)
4.	Rehman Riyaz Ur (3036181630)
5.	Rajesh Arya (30361181800)

<br />

## Work Distribution (Contribution To Project)
- Srivastava Mehul (20%): Game Mechanics, Game Stats and Board Rendering
- Rehman Riyaz Ur (20%): Realtime Leaderboard and Board Rendering
- Rajesh Arya (20%): Random Game Events and Enemy Entity Functionality
- Shoaib Ibrahim (20%): Menu Screens and Spaceship Functionality
- Poon Tsz Hin (20%): Compiling Everything and Gluing Features Together

<br />

## Game Description
Cosmic Intruders is an exciting arcade-style game where your goal is to defend the Earth from waves of alien enemies. As a player, you control a powerful spaceship equipped with a laser cannon. Your mission is to shoot down as many alien invaders as possible before they overwhelm you.

The game is high-score based, meaning there is no definitive end to the game. Your objective is to achieve the highest score possible by eliminating as many aliens as you can. Each alien you successfully shoot will change color and disappear, indicating damage and destruction.

As you progress in the game, the alien enemies become faster and more challenging to defeat. This gradual increase in difficulty adds excitement and tests your reflexes and aiming skills.
You begin the game with three lives. Losing a life occurs when an alien enemy collides reaches the left-end of your screen. When you lose all your lives, the game ends, and your final score is displayed prominently on the side of the game window.

During gameplay, you have the option to activate a power-up by pressing the "p" button. This power-up allows you to shoot multiple missiles simultaneously, increasing your firepower and the chances of hitting alien enemies. You can use this power-up three times during a single game, so use it strategically to maximize your score.

To control your spaceship, use the W, A, S, and D keys. Pressing W moves your spaceship up, A moves it to the left, S moves it down, and D moves it to the right. Use these controls to dodge enemy fire and position yourself for optimal shooting opportunities.

Additionally, the game features a leaderboard option in the game menu, allowing you to check and compare your score with other players. You can also access the credits section to view the game's creators and contributors.
When you're ready to play, choose the "Play Game" option and embark on an exciting adventure to defend Earth against the cosmic intruders. Good luck, and may your shooting skills bring glory and high scores!

<br />

## List Of Features Implemented
- Random enemy generation which is done in waves, with each wave having more enemies and at a faster velocity
- A game stats window that stores game status (using arrays, structs and classes) and lets you see the number of lives and powerups remaing, also the number of enemies you killed as well as the current wave you are facing
- Vectors (STL containers) in almost all entities which include: leaderboard, missiles, enemies, and spaceship
- A "realtime" leaderboard functionality which lets you see your score against the other players who have played the game
- Divided into multiple smaller chunks of modules for code-splitting and easy compilation
- Multiple screens to display menu, rules, leaderboard, credits and the game itself
- Arrow keys functionality to move the spaceship around on the map
- `n-curses` was the only non-standard C++ library used for this project

<br />

## Quick Start
In order to run the game, use the following commands:
```bash
>> make
>> ./main
```

<br />

## Links
Github Repo: https://github.com/mehul-srivastava/Group-33-ENGG1340

Video Link: https://drive.google.com/file/d/1NUYUgv-gXK-BDlmBTVJPHlngvatUYBBv/view?usp=sharing
