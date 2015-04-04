#include <stdlib.h>
#include "level.h"

Level *level;

void create_level( void )
{
	int i, x;

	level = malloc( sizeof( Level ) );
	if ( level == NULL ) {
		return;
	}

	level->width = 40;
	level->height = 20;
	
	level->tiles = calloc( level->height, sizeof( int * ) );
	if ( level->tiles == NULL ) {
		destroy_level();
		return;
	}

	for ( i = 0; i < level->height; i++ ) {
		level->tiles[ i ] = calloc( level->width, sizeof( int ) );
		if ( level->tiles[ i ] == NULL ) {
			destroy_level();
			return;
		}

		for ( x = 0; x < level->width; x++ ) {
			level->tiles[ i ][ x ] = TILE_GRASS_FLOOR;
		}
	}
}

void destroy_level( void )
{
	int i;

	if ( level == NULL ) {
		return;
	}

	if ( level->tiles != NULL ) {
		for ( i = 0; i < level->height; i++ ) {
			if ( level->tiles[ i ] == NULL ) {
				break;
			}
			free( level->tiles[ i ] );
		}
		free( level->tiles );
	}

	free( level );
}

Level *get_level( void )
{
	return level;
}
