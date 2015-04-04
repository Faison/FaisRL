#include <stdlib.h>
#include <ncurses.h>
#include "tile_renderer.h"
#include "ncurses_colors.h"

chtype tile_char_map[] = {
	[TILE_FORM_EMPTY] = ' ',
	[TILE_FORM_FLOOR] = '.',
	[TILE_FORM_WALL]  = '#',
	[TILE_FORM_PATH]  = ',',
	[TILE_FORM_PAVED] = 126 | A_ALTCHARSET
};

void render_tile( enum Tile_Type type )
{
	int color_pair;
	Tile *tile;

	tile = get_tile_by_type( type );

	if ( tile == NULL ) {
		return;
	}

	color_pair = get_color_pair_for_tile_mat( tile->material );

	// No color for the tile material
	if ( -1 == color_pair ) {
		return;
	}

	// Make sure we have a character mapped for the specified tile form
	if ( tile->form < 0 || tile->form > ( sizeof( tile_char_map ) / sizeof( tile_char_map[0] ) ) ) {
		return;
	}

	color_pair_on( color_pair );
	addch( tile_char_map[ tile->form ] );
	color_pair_off( color_pair );
}
