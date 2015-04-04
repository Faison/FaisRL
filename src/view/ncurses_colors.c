#include <ncurses.h>
#include "ncurses_colors.h"

typedef struct fzrl_color_pair {
	short foreground;
	short background;
} FZRL_Color_Pair;

enum FZRL_Color_Pair_Key {
	CP_DEFAULT,
	CP_BROWN,
	CP_GREY,
	CP_GREEN,
	CP_BLUE
};

FZRL_Color_Pair fzrl_color_pairs[] = {
	[CP_DEFAULT] = { .foreground = COLOR_WHITE,  .background = COLOR_BLACK }, // Not used
	[CP_BROWN]   = { .foreground = COLOR_YELLOW, .background = COLOR_BLACK },
	[CP_GREY]    = { .foreground = COLOR_WHITE,  .background = COLOR_BLACK },
	[CP_GREEN]   = { .foreground = COLOR_GREEN,  .background = COLOR_BLACK },
	[CP_BLUE]    = { .foreground = COLOR_BLUE,   .background = COLOR_BLACK }
};

int color_pairs_to_mats[] = {
	[TILE_MAT_EMPTY] = CP_DEFAULT,
	[TILE_MAT_DIRT]  = CP_BROWN,
	[TILE_MAT_STONE] = CP_GREY,
	[TILE_MAT_GRASS] = CP_GREEN,
	[TILE_MAT_WATER] = CP_BLUE,
	[TILE_MAT_WOOD]  = CP_BROWN
};

void init_color_pairs( void )
{
	int i;

	start_color();
	
	for ( i = 1; i < ( sizeof( fzrl_color_pairs ) / sizeof( fzrl_color_pairs[ 0 ] ) ); i++ ) {
		init_pair( i, fzrl_color_pairs[ i ].foreground, fzrl_color_pairs[ i ].background );
	}
}

int get_color_pair_for_tile_mat( enum Tile_Material mat )
{
	if ( mat < 0 || mat > ( sizeof( color_pairs_to_mats ) / sizeof( color_pairs_to_mats[0] ) ) ) {
		return -1;
	}

	return color_pairs_to_mats[ mat ];
}

void color_pair_on( int color_pair )
{
	attron( COLOR_PAIR( color_pair ) );
}

void color_pair_off( int color_pair )
{
	attroff( COLOR_PAIR( color_pair ) );
}
