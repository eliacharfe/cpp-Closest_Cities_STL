#include "Location.h"


std::ostream& operator<<(std::ostream& os, const Location& location)
{
    os << "(" << location.x << "," << location.y << ")";
    	return os;
}
//----------------------------------
const bool operator<(const Location& loc1, const Location& loc2)
{
    return loc1.x < loc2.x;
}
