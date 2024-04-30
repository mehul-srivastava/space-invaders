main: main.o Board.o Spaceship.o Sprite.o Missile.o Enemy.o Menu.o Game.o
		g++ -std=c++11 $^ -o $@ -lncurses

main.o: main.cpp
		g++ -std=c++11 -c $<

Board.o: src/Board.cpp src/Board.h exports/Exports.h src/Sprite.h
		g++ -std=c++11 -c $<

Spaceship.o: src/Spaceship.cpp src/Spaceship.h exports/Exports.h src/Sprite.h
		g++ -std=c++11 -c $<

Missile.o: src/Missile.cpp src/Missile.h exports/Exports.h src/Sprite.h
		g++ -std=c++11 -c $<

Enemy.o: src/Enemy.cpp src/Enemy.h exports/Exports.h src/Sprite.h
		g++ -std=c++11 -c $<

Sprite.o: src/Sprite.cpp src/Sprite.h
		g++ -std=c++11 -c $<

Menu.o: src/Menu.cpp src/Menu.h src/Game.h exports/Exports.h
		g++ -std=c++11 -c $<

Game.o: src/Game.cpp src/Game.h src/Spaceship.h src/Board.h src/Enemy.h src/Missile.h
		g++ -std=c++11 -c $<

clean:
		rm -f main *.o

.PHONY: clean