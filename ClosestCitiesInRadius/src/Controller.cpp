#include "Controller.h"


Controller::Controller()
{
	const string FILE_NAME = "data.txt";

	try {
		openFile(FILE_NAME);
		initMaps();
	}
	catch (FileError& e) { e.what(); throw; }
	catch (std::ifstream::failure& e) { e.what(); throw; }
	catch (...) { throw; }
}
//-------------------------
void Controller::run()
{
	try {
		auto city = string();
		while ((city = getCityNameInput()) != END)
		{
			m_radius = getRadiusInput();
			auto distanceFunc = getDistanceFunction();

			const Location& cityLocation = m_unordMapCities[city];

			multimap < Location, string, LessX > mMapSquare;
			multimap < double, string> sortedSquare;

			createSquareByRadius(mMapSquare, cityLocation);
			createSortedSquare(mMapSquare, sortedSquare, distanceFunc, cityLocation);

			printResults(sortedSquare, cityLocation);

			clearInput();
		}
	}
	catch (InputError& e) {
		cout << e.what() << endl; throw;
	}
	catch (std::exception& e) { throw; }
}
//------------------------------------------------------------------------------
void Controller::createSquareByRadius(multimap<Location, string, LessX>& mMapSquare, const Location& cityLocation)const
{
	static const auto lambdaCompare = [](const pair<Location, string>& p1, const pair<Location, string>& p2) {
		return p1.first.x < p2.first.x;
	};

	auto itBeginX = m_multMapX.lower_bound(Location(cityLocation.x - m_radius, cityLocation.y));
	auto itEndX   = m_multMapX.upper_bound(Location(cityLocation.x + m_radius, cityLocation.y));
	auto itBeginY = m_multMapY.lower_bound(Location(cityLocation.x, cityLocation.y - m_radius));
	auto itEndY   = m_multMapY.upper_bound(Location(cityLocation.x, cityLocation.y + m_radius));

	multimap < Location, string, LessX > subMmapY(itBeginY, itEndY);

	std::set_intersection(itBeginX, itEndX, subMmapY.begin(), subMmapY.end(),
		std::inserter(mMapSquare, mMapSquare.begin()), lambdaCompare);
}
//---------------------------------------------
void Controller::createSortedSquare(const multimap<Location, string, LessX>& mMapSquare, multimap<double, string>& sortedSquare,
	FunctionPtr distanceFunc, const Location& cityLocation) const
{
	const auto lambdaCalcDistance = [&sortedSquare, distanceFunc, cityLocation](const pair<Location, string>& p) {
		sortedSquare.emplace(distanceFunc(cityLocation, p.first), p.second);
	};
	std::for_each(mMapSquare.begin(), mMapSquare.end(), lambdaCalcDistance);
}
//----------------------------------------------------
void Controller::printResults(const multimap<double, string>& sortedSquare, const Location& cityLocation) 
{
	const auto nearest = ++sortedSquare.begin();
	const auto farest = sortedSquare.upper_bound(m_radius); // take circle

	const auto lambdaNorthCitiesInRadius = [this, cityLocation](const pair<double, string>& pair) -> bool {
		return m_unordMapCities[pair.second].y < cityLocation.y;
	};

	cout << endl <<  "\t" << SEARCH_RESULT << endl;
	cout << std::distance(nearest, farest) << NUM_CITIES_IN_RADIUS << endl;
	cout << std::count_if(nearest, farest, lambdaNorthCitiesInRadius) << NUM_CITIES_NORTH << endl << endl;

	cout << "\t" << CLOSEST_CITIES << endl;
	for (auto it = nearest; it != farest; ++it) 
		cout << it->second << endl;
}
//------------------------------------------
void Controller::openFile(const string& nameFile)
{
	m_textFile.close();
	m_textFile.open(nameFile);

	if (!m_textFile.is_open())
		throw FileError(FILE_OPEN_ERR);
}
//----------------------------------
void Controller::initMaps()
{
	string strCity, strLocationX, strLocationY, middle, endline;

	while (m_textFile)
	{
		if (!getline(m_textFile, strCity) && !m_textFile.eof())
			throw FileError(READ_FILE_ERR);

		m_textFile >> strLocationX >> middle >> strLocationY;
		if (!m_textFile && !m_textFile.eof())
			throw FileError(READ_FILE_ERR);

		Location location;
		if (!strLocationX.empty() && !strLocationY.empty()) {
			location.x = std::stod(strLocationX);
			location.y = std::stod(strLocationY);
		}

		m_unordMapCities.emplace(strCity, location);

		m_multMapX.emplace(location, strCity); // sorted by x
		m_multMapY.emplace(location, strCity); // sorted by y

		if (!getline(m_textFile, endline) && !m_textFile.eof())
			throw FileError(READ_FILE_ERR);
	}

	m_textFile.close();
}
//---------------------------------
string Controller::getCityNameInput() const
{
	auto city = string();
	while (cout << ENTER_CITY && std::getline(cin, city)) {
		if (m_unordMapCities.find(city) != m_unordMapCities.end() || city == END)
			return city;
	}
	return city; // never
}
//----------------------------------
double Controller::getRadiusInput() const
{
	auto radius = 1.0;
	while (cout << ENTER_RADIUS) {
		cin >> radius;
		if (cin.fail() || !cin.good()) 
			throw InputError();

		if (radius < 0) {
			cout << RADIUS_OUT_OF_RANGE << endl;
			clearInput();
			continue;
		}	
		break;
		
	}
	return radius;
}
//-----------------------------------
FunctionPtr Controller::getDistanceFunction() const
{
	FunctionPtr distanceFunc;
	int funcNorm;
	
	while (cout << ENTER_NORM) {
		cin >> funcNorm;
		if (cin.fail() || !cin.good())
			throw InputError();

		if (!(distanceFunc = getFunction(funcNorm))) {
			cout << NO_SUCH_FUNC;
			clearInput();
			continue;
		}
		break;
	}

	return distanceFunc;
}
//-----------------------------
void Controller::clearInput() const
{
	cin.clear();
	cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
}
