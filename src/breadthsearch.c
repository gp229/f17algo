#include "simple_logger.h"
#include <SDL.h>
#include <string.h>
#include "breadthsearch.h"

PathResult* bfs(TileMap* tilemap)
{
	Node *queue = NULL;
	Vertex *vertices = NULL;
	Vertex *tempVertex = NULL;
	Vertex *anotherVertex = NULL;
	PathResult *paths = NULL;
	int Foundit = 0;
	Vector2D *result;
	Vector2D current;
	void *data;
	int i = 0;
	int xCount = 0;
	int yCount = 0;
	int iStart = 0;

	vertices = (Vertex *)malloc(sizeof(Vertex) *(tilemap->width * tilemap->height));
	if (!vertices)
	{
		slog("unable to allocate graph");
		return NULL;
	}
	memset(vertices, 0, (sizeof(Vertex)*(tilemap->height * tilemap->width)));
	i = tilemap->width * tilemap->height;
	//Create an array of Vertex structs that are mapped to x and y coordinates.
	for (i = 0; i < (tilemap->width * tilemap->height); i++)
	{
		Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
		vertex->data = (int)tilemap->map[i] - '0';
		vertex->visited = 0;
		vertex->x = xCount;
		vertex->y = yCount;
		vertex->parent = NULL;
		vertices[i] = *vertex;
		//printf("i: %i x: %i y: %i value: %i\n", i, xCount, yCount, temp);
		//printf("%i", tilemap->map[i] - '0');
		if (xCount == tilemap->start.x && yCount == tilemap->start.y)
		{
			iStart = i;
		}
		xCount++;
		if (xCount == tilemap->width)
		{
			//printf("\n");
			xCount = 0;
			yCount++;
		}

	}
	i = 0;
	vertices[iStart].visited = 1;
	queue = enqueue(queue, &vertices[iStart]);
	while (queue != NULL)
	{
		tempVertex = data = dequeue(&queue);
		current = vector2d(tempVertex->x, tempVertex->y);
		if (tempVertex->x == tilemap->end.x && tempVertex->y == tilemap->end.y)
		{
			Foundit = 1;
			printf("Found it");
			while (queue != NULL)
			{
				dequeue(&queue);
			}
			break;
		}
		//up
		current.y = current.y + 1;
		if(current.y <= tilemap->height)
		{
			i = (int)current.y * tilemap->width;
			i += (int)current.x;
			if (vertices[i].visited == 0 && (int)vertices[i].data == 0)
			{
				vertices[i].visited = 1;
				vertices[i].parent = tempVertex;
				queue = enqueue(queue, &vertices[i]);
			}
		}
		current.y = current.y - 1;

		//right
		current.x = current.x + 1;
		if(current.x <= tilemap->width)
		{
			i = (int)current.y * tilemap->width;
			i += (int)current.x;
			if (vertices[i].visited == 0 && (int)vertices[i].data == 0)			
			{
				vertices[i].visited = 1;
				vertices[i].parent = tempVertex;
				printf("x: %i, y: %i \n", vertices[i].x, vertices[i].y);
				queue = enqueue(queue, &vertices[i]);
			}
		}
		current.x = current.x - 1;

		//left
		current.x = current.x - 1;
		if(current.x >= 0)
		{
			i = (int)current.y * tilemap->width;
			i += (int)current.x;
			if (vertices[i].visited == 0 && (int)vertices[i].data == 0)			
			{
				vertices[i].visited = 1;
				vertices[i].parent = tempVertex;
				printf("x: %i, y: %i \n", vertices[i].x, vertices[i].y);
				queue = enqueue(queue, &vertices[i]);
			}
		}
		current.x = current.x + 1;

		//down
		current.y = current.y - 1;
		if(current.y >= 0)
		{
			i = (int)current.y * tilemap->width;
			i += (int)current.x;
			if (vertices[i].visited == 0 && (int)vertices[i].data == 0)
			{
				vertices[i].visited = 1;
				vertices[i].parent = tempVertex;
				printf("x: %i, y: %i \n", vertices[i].x, vertices[i].y);
				queue = enqueue(queue, &vertices[i]);
			}
		}
		current.y = current.y + 1;
	}
	if (Foundit == 1) 
	{
		i = 0;
		anotherVertex = tempVertex;
		while (anotherVertex->parent != NULL)
		{
			i++;
			anotherVertex = anotherVertex->parent;
		}
		result = (Vector2D*)malloc(sizeof(Vector2D) *i);
		if (!result)
		{
			slog("unable to allocate result");
			return NULL;
		}
		memset(result, 0, (sizeof(Vector2D)*i));

		paths = (PathResult *)malloc(sizeof(PathResult));
		if (!paths)
		{
			slog("unable to allocate paths");
			return NULL;
		}
		memset(paths, 0, (sizeof(PathResult)));
		paths->arraysize = i;
		while (tempVertex != NULL) //don't need the starting point
		{
			current.x = tempVertex->x;
			current.y = tempVertex->y;
			result[i] = current;
			i--;
			tempVertex = tempVertex->parent;
		}
		paths->values = result;

		return paths;
	}
	return NULL;	

}