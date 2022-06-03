#pragma once
#include "Location.h"

typedef struct LessX
{
	bool operator()(const Location& loc1, const Location& loc2) const {
		return loc1.x < loc2.x;
	}

} LessX;
//------------------------------
typedef struct LessY
{
	bool operator()(const Location& loc1, const Location& loc2) const {
		return loc1.y < loc2.y;
	}

} LessY;
