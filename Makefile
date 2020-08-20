libs ?= -lSDL2 


ALL := MoonLander

MoonLander: obj/MoonLander.o
	g++ obj/*.o -o MoonLander $(libs) `sdl2-config --cflags --libs`

obj/%.o: src/%.cpp #src/MLhelper.h
	$(info $< => $@)
	g++ -c $< -o $@ `sdl2-config --cflags --libs`


clean:
	rm obj/*.o
	