#ifndef FRACTION_HPP_
#define FRACTION_HPP_

#include <string>
#include <map>

class Fraction {
	std::string mName;
	std::string mDescription;
public:
	const std::string & getName() const;
	const std::string & getDescription() const;

	Fraction() = default;
	Fraction(std::string name, std::string description);
	virtual ~Fraction() = default;
};

std::map<int, Fraction> loadFractions(std::string file);

#endif /* FRACTION_HPP_ */
