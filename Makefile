
output: main.o
	g++ main.o -o PingPong -lglut -lGLU -lGL -lglfw -lm -lpthread -lGLEW

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o PingPong
