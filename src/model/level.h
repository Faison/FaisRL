#ifndef FZRL_LEVEL_H
#define FZRL_LEVEL_H

#include "tile.h"

typedef struct fzrl_level {
	int width;
	int height;
	int **tiles;
} Level;

void create_level( void );
void destroy_level( void );

Level *get_level( void );

#endif
