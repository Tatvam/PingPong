
output: main.o standfunc.o Tile.o timer.o
	g++ main.o standfunc.o Tile.o timer.o -o PingPong -lglut -lGLU -lGL -lglfw -lm -lpthread -lGLEW

main.o: main.cpp standfunc.cpp Tile.cpp timer.cpp
	g++ -c main.cpp standfunc.cpp Tile.cpp timer.cpp

clean:
	rm *.o PingPong
