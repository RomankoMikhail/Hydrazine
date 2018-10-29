#include "Application.hpp"
#include "Fraction.hpp"

int main(int argc, char ** argv) {
	std::map<int, Fraction> fracs = loadFractions("data/fractions.xml");

	Application myApp;

	myApp.run(argc, argv);

	return 0;
}
