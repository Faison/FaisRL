#ifndef FZRL_NCURSES_COLORS_H
#define FZRL_NCURSES_COLORS_H

#include "../model/tile_types.h"

void init_color_pairs( void );
int get_color_pair_for_tile_mat( enum Tile_Material mat );

void color_pair_on( int color_pair );
void color_pair_off( int color_pair );

#endif
