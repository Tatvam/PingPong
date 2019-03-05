
output: main.o standfunc.o Tile.o
	g++ main.o standfunc.o Tile.o -o PingPong -lglut -lGLU -lGL -lglfw -lm -lpthread -lGLEW

main.o: main.cpp standfunc.cpp Tile.cpp
	g++ -c main.cpp standfunc.cpp Tile.cpp

clean:
	rm *.o PingPong
