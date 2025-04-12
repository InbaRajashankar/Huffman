FLAGS := -std=c++17 -Wall -Wextra

huff: main.o encode.o decode.o io.o node.o
	g++ $(FLAGS) $^ -o huff

end2end: huff
	python3 tests/end2end_tests/end2end.py

encode: encode.o node.o
	g++ $(FLAGS) $^ -o encode

decode: decode.o node.o
	g++ $(FLAGS) $^ -o decode

io: io.o
	g++ $(FLAGS) $^ -o io

main.o: src/main.cpp src/node.h src/encode.h src/decode.h src/io.h
	g++ $(FLAGS) -c $< -o main.o

encode.o: src/encode.cpp src/encode.h src/node.h
	g++ $(FLAGS) -c $< -o encode.o

decode.o: src/decode.cpp src/decode.h src/node.h
	g++ $(FLAGS) -c $< -o decode.o

node.o: src/node.cpp src/node.h
	g++ $(FLAGS) -c $< -o node.o

io.o: src/io.cpp src/io.h
	g++ $(FLAGS) -c $< -o io.o

clean:
	rm -rf *.o huff encode decode io