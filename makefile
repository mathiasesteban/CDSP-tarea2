obj/bitio.o: src/bitio.h src/bitio.cpp
	g++ -c src/bitio.cpp -o obj/bitio.o

obj/coder.o: src/coder.h src/coder.cpp
	g++ -c src/coder.cpp -o obj/coder.o

obj/compressor.o: src/bitio.h src/coder.h src/symbol.h src/compressor.h src/compressor.cpp
	g++ -c src/compressor.cpp -o obj/compressor.o

obj/decompressor.o: src/bitio.h src/coder.h src/symbol.h src/decompressor.h src/decompressor.cpp
	g++ -c src/decompressor.cpp -o obj/decompressor.o

objs: obj/bitio.o obj/coder.o obj/compressor.o obj/decompressor.o

all: objs
	g++ main.cpp obj/* -o tarea2

clean:
	rm obj/*
	rm tarea2
