#pragma once
#include "Utilities.h"
#include "Less.h"
#include "Exception.h"
#include "Function.h"

class Controller
{
public:
	Controller();

	void run();

private:
	double m_radius;
	ifstream m_textFile;

	unordered_map < string, Location > m_unordMapCities;

	multimap < Location, string, LessX > m_multMapX;
	multimap < Location, string, LessY > m_multMapY;

	void createSquareByRadius(multimap < Location, string, LessX >&, const Location&) const;
	void createSortedSquare(const multimap < Location, string, LessX >& mMapSquare, multimap < double, string >& sortedSquare,
	                        FunctionPtr distanceFunc, const Location& cityLocation) const;

	void printResults(const multimap < double, string >& sortedSquare, const Location& cityLocation) ;

	void openFile(const string& fileName);
	void initMaps();

	string getCityNameInput() const;
	double getRadiusInput() const;
	FunctionPtr getDistanceFunction() const;

	void clearInput() const;
};