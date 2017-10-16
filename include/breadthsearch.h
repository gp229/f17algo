#pragma once
#ifndef __BREADTHSEARCH_H__
#define __BREADTHSEARCH_H__

#include "tilemap.h"
#include "linkedlist.h"
#include "gf2d_vector.h"

typedef struct Vertex_S Vertex;

struct Vertex_S {
	int data;
	int visited;
	int x;
	int y;
	struct Vertex_S *parent;
};

typedef struct {
	Vector2D *values;
	int arraysize;
}PathResult;

PathResult* bfs(TileMap* tilemap);
#endif