#ifndef FZRL_TILE_H
#define FZRL_TILE_H

#include "tile_types.h"

/**
 * Public Tile Functions and Defines
 *
 * Tile Explanation:
 * - Tiles have a material type (e.g. dirt, grass, stone, wood, metal, water, fire, empty)
 * - Tiles have a form type (e.g. floor, path, paved, wall, empty)
 * - Material Types and Form Types have movement values (e.g. dirt floor < dirt path < paved stone)
 * - Material Types and Form Types have passability values (e.g. not passable, passable)
 */

typedef struct fzrl_tile {
	enum Tile_Material material;
	enum Tile_Form     form;
} Tile;

enum Tile_Type {
	TILE_EMPTY,
	TILE_DIRT_FLOOR,
	TILE_GRASS_FLOOR,
	TILE_STONE_FLOOR,
	TILE_DIRT_WALL,
	TILE_STONE_WALL,
	TILE_GRASS_PAVED
};

Tile *get_tile_by_type( enum Tile_Type type );

#endif
