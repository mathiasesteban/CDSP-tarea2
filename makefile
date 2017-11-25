obj/bitio.o: src/bitio.h src/bitio.cpp
	g++ -std=c++11 -c src/bitio.cpp -o obj/bitio.o

obj/coder.o: src/coder.h src/coder.cpp
	g++ -std=c++11 -c src/coder.cpp -o obj/coder.o

obj/initialize_probabilities.o: src/utils.h src/utils/initialize_probabilities.cpp
	g++ -std=c++11 -c src/utils/initialize_probabilities.cpp -o obj/initialize_probabilities.o

obj/update_probabilities.o: src/utils.h src/utils/update_probabilities.cpp
	g++ -std=c++11 -c src/utils/update_probabilities.cpp -o obj/update_probabilities.o

obj/imprimir_estadistica.o: src/utils.h src/utils/imprimir_estadistica.cpp
	g++ -std=c++11 -c src/utils/imprimir_estadistica.cpp -o obj/imprimir_estadistica.o

obj/change_state.o: src/utils.h src/utils/change_state.cpp
	g++ -std=c++11 -c src/utils/change_state.cpp -o obj/change_state.o

obj/compressor.o: src/bitio.h src/coder.h src/symbol.h src/compressor.h src/utils.h src/compressor.cpp
	g++ -std=c++11 -c src/compressor.cpp -o obj/compressor.o

obj/decompressor.o: src/bitio.h src/coder.h src/symbol.h src/decompressor.h src/utils.h src/decompressor.cpp
	g++ -std=c++11 -c src/decompressor.cpp -o obj/decompressor.o

objs: obj/bitio.o obj/coder.o obj/initialize_probabilities.o obj/update_probabilities.o obj/imprimir_estadistica.o obj/change_state.o obj/compressor.o obj/decompressor.o

all: objs
	g++ -std=c++11 main.cpp obj/* -o tarea2

clean:
	rm obj/*
	rm tarea2
