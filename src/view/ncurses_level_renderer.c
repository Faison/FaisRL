#include <stdlib.h>
#include <ncurses.h>
#include "level_renderer.h"

void render_level( Level *level )
{
	int y, x;

	// Make sure we have a valid level
	if ( level == NULL ) {
		return;
	}

	if ( level->width <= 0 || level->height <= 0 ) {
		return;
	}

	if ( level->tiles == NULL ) {
		return;
	}

	for ( y = 0; y < level->height; y++ ) {
		move( y, 0 );
		for ( x = 0; x < level->width; x++ ) {
			render_tile( level->tiles[ y ][ x ] );
		}
	}
}
