#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

#include "model/level.h"
#include "view/ncurses_colors.h"
#include "view/level_renderer.h"

#define MAP_WIDTH  40
#define MAP_HEIGHT 20

bool is_passable( int x, int y );
void show_inventory( void );
void get_command( void );
void drop_command( void );
void use_item_command( void );

#define ITEM_EMPTY  0
#define ITEM_POTION 1
#define ITEM_ROCK   2
#define ITEM_KEY    3
#define ITEM_AXE    4

typedef struct fais_item_type {
	char character;
	int color_pair;
	char *name;
} Item_Type;

Item_Type item_index[] = {
	{ ' ', 0, "EMPTY" },  // ITEM_EMPTY
	{ '!', 4, "Potion" }, // ITEM_POTION
	{ '*', 0, "Rock" },   // ITEM_ROCK
	{ '`', 4, "Key" },    // ITEM_KEY
	{ '(', 4, "Pickaxe" } // ITEM_AXE
};

#define INVENTORY_SLOTS 10

int item_array[ MAP_HEIGHT ][ MAP_WIDTH ];
int inventory[ INVENTORY_SLOTS ];

int player_x = 4;
int player_y = 4;

int main( void )
{
	int dx = 0, dy = 0, c = '\0';
	Level *level;

	memset( inventory, 0, sizeof(inventory) );
	memset( item_array, 0, sizeof(item_array) );

	inventory[0] = ITEM_ROCK;

	item_array[9][6] = ITEM_AXE;
	item_array[4][12] = ITEM_POTION;
	item_array[3][4] = ITEM_KEY;

	create_level();
	level = get_level();

	initscr();
	raw();
	keypad(stdscr, TRUE);
	curs_set(0);
	noecho();
	init_color_pairs();

	while ( c != '\n') {
		// Output
		clear();

		render_level( level );

		show_inventory();

		attron(COLOR_PAIR(2));
		mvaddch(player_y, player_x, '@');
		attroff(COLOR_PAIR(2));
		refresh();

		// Input
		c = getch();

		// Logic
		if (c == KEY_DOWN) {
			dx = 0;
			dy = 1;
		} else if (c == KEY_LEFT) {
			dx = -1;
			dy = 0;
		} else if (c == KEY_RIGHT) {
			dx = 1;
			dy = 0;
		} else if (c == KEY_UP) {
			dx = 0;
			dy = -1;
		} else {
			dx = 0;
			dy = 0;
		}

		if (c == 'o') {
		} else if (c == 'c') {
		} else if (c == 'g') {
			get_command();
		} else if (c == 'd') {
			drop_command();
		} else if (c == 'u') {
			use_item_command();
		}

		if ((dx != 0 || dy != 0) && is_passable(player_x + dx, player_y + dy)) {
			player_x += dx;
			player_y += dy;
		}
	}

	endwin();

	destroy_level();

	return 0;
}

bool is_passable( int x, int y )
{
	int type_index;

	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
		return false;
	}

	return true;
}

void show_inventory( void )
{
	int i, item_type;

	mvprintw(1, MAP_WIDTH + 2, "INVENTORY");
	mvprintw(2, MAP_WIDTH + 2, "---------");

	for (i = 0; i < INVENTORY_SLOTS; i++) {
		item_type = inventory[i];

		mvprintw(3 + i, MAP_WIDTH + 2, "%c: %s", 'A' + i, item_index[item_type].name);
	}	
}

void get_command( void )
{
	int i;

	if (item_array[player_y][player_x] == ITEM_EMPTY) {
		return;
	}

	for (i = 0; i < INVENTORY_SLOTS; i++) {
		if (inventory[i] == ITEM_EMPTY) {
			inventory[i] = item_array[player_y][player_x];
			item_array[player_y][player_x] = ITEM_EMPTY;
			return;
		}
	}

	return;
}

void drop_command( void )
{
	int c, slot;
	mvprintw(MAP_HEIGHT + 2, 2, "Drop from which slot?");
	c = getch();

	slot = c - 'a';

	if (slot < 0 || slot >= INVENTORY_SLOTS) {
		mvprintw(MAP_HEIGHT + 3, 2, "Invalid Slot");
		getch();
		return;
	}

	if (inventory[slot] == ITEM_EMPTY) {
		mvprintw(MAP_HEIGHT + 3, 2, "No item present");
		getch();
		return;
	}

	if (item_array[player_y][player_x] != ITEM_EMPTY) {
		mvprintw(MAP_HEIGHT + 3, 2, "No room to drop item");
		getch();
		return;
	}

	item_array[player_y][player_x] = inventory[slot];
	inventory[slot] = ITEM_EMPTY;
}

void use_item_command( void )
{
	int c, slot;

	mvprintw(MAP_HEIGHT + 2, 2, "Use which item?");
	c = getch();

	slot = c - 'a';

	if (slot < 0 || slot >= INVENTORY_SLOTS) {
		mvprintw(MAP_HEIGHT + 3, 2, "Invalid Slot");
		getch();
		return;
	}

	if (inventory[slot] == ITEM_EMPTY) {
		mvprintw(MAP_HEIGHT + 3, 2, "No item to use!");
		getch();
	} else if (inventory[slot] == ITEM_POTION) {
		mvprintw(MAP_HEIGHT + 3, 2, "You drink the potion. *burp!*");

		inventory[slot] = ITEM_EMPTY;

		getch();
	} else {
		mvprintw(MAP_HEIGHT + 3, 2, "Don't know how to use this item!");
		getch();
	}
	
}
