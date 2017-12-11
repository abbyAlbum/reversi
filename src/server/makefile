# Abby Album
# 340907138
# Eyal Moskowitz
# 314074303
target: Server.o main.o
	g++ -o ../../exe/server.out main.o Server.o
	rm -f *.o

Server.o: Server.cpp Server.h
	g++ -c Server.cpp

main.o: main.cpp Server.h
	g++ -c main.cpp
