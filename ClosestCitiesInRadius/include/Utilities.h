#pragma once

#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>

using std::unordered_map;
using std::multimap;
using std::pair;
using std::vector;
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::ifstream;
using std::ofstream;
using std::to_string;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;

namespace {
	const string END = "0";
	const string ENTER_CITY = "Please enter selected city name (with line break after it):\n";
	const string ENTER_RADIUS = "Please enter the wanted radius:\n";
	const string ENTER_NORM = "Please enter the wanted norm(0 – L2, Euclidean distance, 1 – Linf, Chebyshev distance, 2 – L1, Manhattandistance)\n";
	const string RADIUS_OUT_OF_RANGE = "Radius should be greater than 0...\n";
	const string NO_SUCH_FUNC = "No such function\n";
	const string SEARCH_RESULT = "Search result:\n";
	const string NUM_CITIES_IN_RADIUS = " city/cities found in the given radius";
	const string NUM_CITIES_NORTH = " cities are to the north of the selected city";
	const string CLOSEST_CITIES = "City list:\n";

	const char* FILE_OPEN_ERR = "Cannot open file...\n";
	const char* READ_FILE_ERR = "Problem reading text file...\n";
	const char* INVALID_INPUT = "Invalid input";
}