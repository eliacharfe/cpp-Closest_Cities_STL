#pragma once
#include "Utilities.h"

typedef struct Location
{
	double x;
	double y;

	Location() : x(0), y(0){}
	~Location() { }

	Location(double x, double y) : x(x), y(y) {}

} Location;

std::ostream& operator<<(std::ostream& os, const Location& location);
const bool operator<(const Location& loc1, const Location& loc2);


