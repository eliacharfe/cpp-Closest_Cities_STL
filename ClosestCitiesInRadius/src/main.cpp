#include <iostream>
#include "Controller.h"


int main()
{
	try {
		Controller controller;
		controller.run();
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	}

	cout << "Bye" << endl;

	return EXIT_SUCCESS;
}