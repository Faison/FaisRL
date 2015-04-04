CFLAGS = -std=c99
LIBFLAGS = -lncurses

build-ncurses: game-objects ncurses-objects
	mkdir -p build
	gcc -o build/faisrl src/faisrl.c \
		obj/model/{tile.o,level.o} \
		obj/view/{colors.o,tile_renderer.o,level_renderer.o} \
		$(CFLAGS) $(LIBFLAGS)

game-objects:
	mkdir -p obj/model
	gcc -c src/model/tile.c -o obj/model/tile.o $(CFLAGS)
	gcc -c src/model/level.c -o obj/model/level.o $(CFLAGS)

ncurses-objects:
	mkdir -p obj/view
	gcc -c src/view/ncurses_colors.c -o obj/view/colors.o $(CFLAGS)
	gcc -c src/view/ncurses_tile_renderer.c -o obj/view/tile_renderer.o $(CFLAGS)
	gcc -c src/view/ncurses_level_renderer.c -o obj/view/level_renderer.o $(CFLAGS)
