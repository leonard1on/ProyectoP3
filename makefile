main: main.o Start.o Kopemon.o Grass.o Fire.o Water.o Electric.o Attack.o PowerUp.o Offensive.o
	g++ main.o Start.o Kopemon.o Grass.o Fire.o Water.o Electric.o Attack.o PowerUp.o Offensive.o -lncurses -o main

main.o: main.cpp Start.h
	g++ -c main.cpp

Start.o: Start.cpp Start.h Kopemon.h Fire.h Grass.h Electric.h Water.h Attack.h Offensive.h PowerUp.h
	g++ -c Start.cpp

Kopemon.o: Kopemon.cpp Kopemon.h Water.h Attack.h Offensive.h
	g++ -c Kopemon.cpp

Grass.o: Grass.cpp Grass.h Water.h Fire.h Kopemon.h Attack.h Offensive.h PowerUp.h
	g++ -c Grass.cpp

Fire.o: Fire.cpp Fire.h Water.h Grass.h Kopemon.h Attack.h Offensive.h
	g++ -c Fire.cpp

Water.o: Water.cpp Water.h Grass.h Fire.h Kopemon.h Attack.h Offensive.h PowerUp.h
	g++ -c Water.cpp

Electric.o: Electric.cpp Electric.h Water.h Grass.h Kopemon.h Attack.h Offensive.h
	g++ -c Electric.cpp

Attack.o: Attack.cpp Attack.h
	g++ -c Attack.cpp

PowerUp.o: PowerUp.cpp PowerUp.h Attack.h
	g++ -c PowerUp.cpp

Offensive.o: Offensive.cpp Offensive.h Attack.h
	g++ -c Offensive.cpp
