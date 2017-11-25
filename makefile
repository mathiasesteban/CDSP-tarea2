obj/bitio.o: src/bitio.h src/bitio.cpp
	g++ -c src/bitio.cpp -o obj/bitio.o

obj/coder.o: src/coder.h src/coder.cpp
	g++ -c src/coder.cpp -o obj/coder.o

obj/initialize_probabilities.o: src/utils.h src/utils/initialize_probabilities.cpp
	g++ -c src/utils/initialize_probabilities.cpp -o obj/initialize_probabilities.o

obj/update_probabilities.o: src/utils.h src/utils/update_probabilities.cpp
	g++ -c src/utils/update_probabilities.cpp -o obj/update_probabilities.o

obj/change_state.o: src/utils.h src/utils/change_state.cpp
	g++ -c src/utils/change_state.cpp -o obj/change_state.o

obj/compressor.o: src/bitio.h src/coder.h src/symbol.h src/compressor.h src/utils.h src/compressor.cpp
	g++ -c src/compressor.cpp -o obj/compressor.o

obj/decompressor.o: src/bitio.h src/coder.h src/symbol.h src/decompressor.h src/utils.h src/decompressor.cpp
	g++ -c src/decompressor.cpp -o obj/decompressor.o

objs: obj/bitio.o obj/coder.o obj/initialize_probabilities.o obj/update_probabilities.o obj/change_state.o obj/compressor.o obj/decompressor.o

all: objs
	g++ main.cpp obj/* -o tarea2

clean:
	rm obj/*
	rm tarea2
