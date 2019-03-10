
output: main_server.o standfunc.o Tile.o timer.o  ball.o collision.o main_client.o server_udp.o client_udp.o
	g++ main_server.o standfunc.o Tile.o timer.o ball.o collision.o server_udp.o -o PingPong -lglut -lGLU -lGL -lglfw -lm -lpthread -lGLEW
	g++ main_client.o standfunc.o Tile.o timer.o ball.o collision.o client_udp.o -o PingPong1 -lglut -lGLU -lGL -lglfw -lm -lpthread -lGLEW

main.o: main_server.cpp standfunc.cpp Tile.cpp timer.cpp ball.cpp collision.cpp main_client.cpp server_udp.cpp client_udp.cpp
	g++ -c main_server.cpp standfunc.cpp Tile.cpp timer.cpp ball.cpp collision.cpp main_client.cpp server_udp.cpp client_udp.cpp

clean:
	rm *.o PingPong PingPong1
