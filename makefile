main: main.o Start.o Kopemon.o Grass.o Fire.o Water.o Electric.o Attack.o PowerUp.o Offensive.o Scanner.o Material.o Stone.o Element.o Object.o Animal.o Music.o SoundFX.o
	g++ main.o Start.o Kopemon.o Grass.o Fire.o Water.o Electric.o Attack.o PowerUp.o Offensive.o Scanner.o Material.o Stone.o Element.o Object.o Animal.o Music.o SoundFX.o -lSDL -lSDL_mixer -lncurses -o main

main.o: main.cpp Start.h
	g++ -c main.cpp

Start.o: Start.cpp Start.h Kopemon.h Fire.h Grass.h Electric.h Water.h Attack.h Offensive.h PowerUp.h Scanner.h Material.h Element.h Stone.h Object.h Animal.h Music.h
	g++ -c Start.cpp

Object.o: Object.cpp Object.h
	g++ -c Object.cpp

Kopemon.o: Kopemon.cpp Kopemon.h Water.h Attack.h Offensive.h Object.h
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

Scanner.o: Scanner.cpp Scanner.h
	g++ -c Scanner.cpp

Material.o: Material.cpp Material.h Object.h
	g++ -c Material.cpp

Stone.o: Stone.cpp Stone.h Material.h
	g++ -c Stone.cpp

Element.o: Element.cpp Element.h Material.h
	g++ -c Element.cpp

Animal.o: Animal.cpp Animal.h Object.h
	g++ -c Animal.cpp

Music.o: Music.cpp Music.h
	g++ -c Music.cpp

SoundFX.o: SoundFX.cpp SoundFX.h
	g++ -c SoundFX.cpp	
