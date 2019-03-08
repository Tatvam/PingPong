
output: main.o standfunc.o Tile.o timer.o  ball.o
	g++ main.o standfunc.o Tile.o timer.o ball.o -o PingPong -lglut -lGLU -lGL -lglfw -lm -lpthread -lGLEW

main.o: main.cpp standfunc.cpp Tile.cpp timer.cpp ball.cpp
	g++ -c main.cpp standfunc.cpp Tile.cpp timer.cpp ball.cpp

clean:
	rm *.o PingPong
