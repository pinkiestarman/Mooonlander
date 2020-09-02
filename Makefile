libs ?= `sdl2-config --libs`
cflags ?= -Iinclude `sdl2-config --cflags`

ALL := MoonLander

MoonLander: obj/MoonLander.o
	g++ obj/*.o -o MoonLander $(libs) $(cflags)

obj/%.o: src/%.cpp 
	$(info $< => $@)
	g++ -c $< -o $@ $(cflags)


clean:
	rm obj/*.o
	