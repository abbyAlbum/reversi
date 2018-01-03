# Eyal Moskowitz
# 314074303
# Abby Album
# 340907138
target: compileAll
	g++ -o ../../exe/server.out *.o -pthread
	rm -f *.o

compileAll: include/*.h src/*.cpp
	g++ -Iinclude/ -c src/*.cpp
run:
	./server.out
