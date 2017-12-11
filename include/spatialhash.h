#pragma once
#ifndef __SPATIALHASH_H__
#define __SPATIALHASH_H__

#include "gf2d_collision.h"

spatialhash * spatialhash_new(Space *space);
spatialhash * spatialhash_insert(spatialhash *spatialmap, Body *body);
spatialhash * spatialhash_refresh(Space *space);


#endif
	