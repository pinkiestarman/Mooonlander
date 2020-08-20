#obj/spual.o: src/spual.cpp
#	g++ src/spual.cpp -o obj/spual.o -lSDL2 

libs ?= -lSDL2


ALL := spual

spual: obj/spual.o
	g++ obj/*.o -o spual $(libs) `sdl2-config --cflags --libs`

obj/%.o: src/%.cpp
	$(info $< => $@)
	g++ -c $< -o $@ `sdl2-config --cflags --libs`


clean:
	rm obj/*.o