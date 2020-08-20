libs ?= `sdl2-config --libs`
cflags ?= `sdl2-config --cflags`

ALL := MoonLander

MoonLander: obj/MoonLander.o
	g++ obj/*.o -o MoonLander $(libs) $(cflags)

obj/%.o: src/%.cpp src/MLhelper.h
	$(info $< => $@)
	g++ -c $< -o $@ $(cflags)


clean:
	rm obj/*.o
	