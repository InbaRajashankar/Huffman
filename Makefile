FLAGS := -std=c++17 -Wall -Wextra

main: main.o encode.o io.o node.o
	g++ $(FLAGS) $^ -o main

encode: encode.o node.o
	g++ $(FLAGS) $^ -o encode

main.o: src/main.cpp src/node.h src/encode.h src/io.h
	g++ $(FLAGS) -c $< -o main.o

encode.o: src/encode.cpp src/encode.h src/node.h
	g++ $(FLAGS) -c $< -o encode.o

node.o: src/node.cpp src/node.h
	g++ $(FLAGS) -c $< -o node.o

io.o: src/io.cpp src/io.h
	g++ $(FLAGS) -c $< -o io.o

clean:
	rm -rf *.o encode main