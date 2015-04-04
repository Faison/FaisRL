#include <stdlib.h>
#include "tile.h"
#include "tile_types.h"

Tile tile_types[] = {
	[TILE_EMPTY]       = { .material = TILE_MAT_EMPTY, .form = TILE_FORM_EMPTY },
	[TILE_DIRT_FLOOR]  = { .material = TILE_MAT_DIRT,  .form = TILE_FORM_FLOOR },
	[TILE_GRASS_FLOOR] = { .material = TILE_MAT_GRASS, .form = TILE_FORM_FLOOR },
	[TILE_STONE_FLOOR] = { .material = TILE_MAT_STONE, .form = TILE_FORM_FLOOR },
	[TILE_DIRT_WALL]   = { .material = TILE_MAT_DIRT,  .form = TILE_FORM_WALL  },
	[TILE_STONE_WALL]  = { .material = TILE_MAT_STONE, .form = TILE_FORM_WALL },
	[TILE_GRASS_PAVED] = { .material = TILE_MAT_WOOD, .form = TILE_FORM_PAVED }
};

Tile *get_tile_by_type( enum Tile_Type type )
{
	if ( type < 0 || type > ( sizeof( tile_types ) / sizeof( tile_types[0] ) ) ) {
		return NULL;
	}

	return &( tile_types[ type ] );
}
