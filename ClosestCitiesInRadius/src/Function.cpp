#include "Function.h"

namespace
{
	enum functions {
		L2, Linf, L1
	};

	double euclidianDistance(const Location& myCityLoc, const Location& otherCityLoc) {
		// √(𝑥0 − 𝑥1)^2 + (𝑦0 −𝑦1)^2
		return sqrt(pow(myCityLoc.x - otherCityLoc.x, 2) + pow(myCityLoc.y - otherCityLoc.y, 2));
	}

	double infiniteDistance(const Location& myCityLoc, const Location& otherCityLoc) {
		// 𝑚𝑎𝑥(|𝑥0 − 𝑥1| , |𝑦0 − 𝑦1|)
		return std::max(abs(myCityLoc.x - otherCityLoc.x), abs(myCityLoc.y - otherCityLoc.y));
	}

	double manhattanDistance(const Location& myCityLoc, const Location& otherCityLoc) {
		// |𝑥0 − 𝑥1| + |𝑦0 − 𝑦1|
		return abs(myCityLoc.x - otherCityLoc.x) + abs(myCityLoc.y - otherCityLoc.y);
	}

	FuncMap initializeFunctionsMap()
	{
		FuncMap map;
		map[L2] = &euclidianDistance;
		map[Linf] = &infiniteDistance;
		map[L1] = &manhattanDistance;

		return map;
	}
} 
//----------------------------------------------------------------
FunctionPtr getFunction(const char c)
{
	static FuncMap funcMap = initializeFunctionsMap();

	auto mapEntry = funcMap.find(c);
	if (mapEntry == funcMap.end()) 
		return nullptr;
	
	return mapEntry->second;
}










