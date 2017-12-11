#include "spatialhash.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"


spatialhash * spatialhash_new(Space *space)
{
	spatialhash *gridHash = (spatialhash*)malloc(sizeof(spatialhash));
	if(!space) return NULL;
    if (!gridHash)return NULL;
	memset(gridHash, 0, sizeof(spatialhash));
	gridHash->cellsize = 50;
	gridHash->width = space->bounds.w / gridHash->cellsize;
	gridHash->height = space->bounds.h / gridHash->cellsize;
	gridHash->conversionFactor = 1 / (float)gridHash->cellsize;
	gridHash->buckets = gridHash->width * gridHash->height;
	gridHash->hashtable = hash_new(gridHash->buckets);
    return gridHash;
}

spatialhash * spatialhash_insert(spatialhash *spatialmap, Body *body)
{
		int gridcell; 
		int radius;
		int startingColumn, endingColumn, startingRow, endingRow;
		int rowsCount, columnCount;
		int i, j;
		if (!body) return;
		if(body->shape->type == ST_CIRCLE)
		{
			radius = body->shape->s.c.r;
			startingColumn = (body->position.x - radius) * spatialmap->conversionFactor;
			endingColumn = (body->position.x + radius) * spatialmap->conversionFactor;
			startingRow = (body->position.y - radius) * spatialmap->conversionFactor;
			endingRow = (body->position.y + radius) * spatialmap->conversionFactor;
		}
		else if (body->shape->type == ST_RECT)
		{

			startingColumn = (body->position.x - body->shape->s.r.x) * spatialmap->conversionFactor;
			endingColumn = (body->position.x + body->shape->s.r.w) * spatialmap->conversionFactor;
			startingRow = (body->position.y - body->shape->s.r.y) * spatialmap->conversionFactor;
			endingRow = (body->position.y + body->shape->s.r.h) * spatialmap->conversionFactor;
		}
		if (startingColumn < 0)
		{
			startingColumn = 0;
		}
		if (endingColumn > spatialmap->width)
		{
			endingColumn = spatialmap->width;
		}
		if (startingRow < 0)
		{
			startingRow = 0;
		}
		if (endingRow > spatialmap->height)
		{
			endingRow = spatialmap->height;
		}
		startingRow--;
		startingColumn--;
		endingColumn--;
		endingRow--;
		gridcell = startingColumn + startingRow * spatialmap->width;
		columnCount = endingColumn - startingColumn;
		rowsCount = endingRow - startingRow;
		gridcell--;
		for (i = 0; i < rowsCount; i++)
		{
			for (j = 0; j < columnCount; j++)
			{
				gridcell++;
				spatialmap->hashtable = insert(spatialmap->hashtable, gridcell, (void*)body);
			}
			gridcell += spatialmap->width - columnCount;
		}
		return spatialmap;
}

spatialhash * spatialhash_refresh(Space *space)
{
	int bodies, staticShapes;
	int i;
	Body *body;
	Shape *shape;
	keynode *temp;
	if (space->spatialHash)
	{
		space->spatialHash->hashtable = hash_free(space->spatialHash->hashtable);
		free(space->spatialHash);
		space->spatialHash = NULL;
	}
	space->spatialHash = spatialhash_new(space);
	bodies = gf2d_list_get_count(space->bodyList);
	staticShapes = gf2d_list_get_count(space->staticShapes);
	for (i = 0; i < bodies; i++)
	{
		body = (Body*)gf2d_list_get_nth(space->bodyList, i);
		if (!body)continue;
		space->spatialHash = spatialhash_insert(space->spatialHash, body);
	}

	return space->spatialHash;
}



