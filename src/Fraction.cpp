#include "Fraction.hpp"
#include <pugixml.hpp>

const std::string & Fraction::getName() const {
	return mName;
}

const std::string & Fraction::getDescription() const {
	return mDescription;
}

Fraction::Fraction(std::string name, std::string description) {
	mName = name;
	mDescription = description;
}

#include <iostream>

std::map<int, Fraction> loadFractions(std::string file) {
	std::map<int, Fraction> fracs;

	pugi::xml_document doc;
	doc.load_file(file.c_str());

	for (pugi::xml_node & root : doc) {
		if (root.name() == std::string("fractions")) {
			for (pugi::xml_node & fractions : root) {
				if (fractions.name() == std::string("fraction")) {
					fracs[fractions.attribute("id").as_int()] = Fraction(fractions.attribute("name").as_string(), fractions.child_value());
					std::cout << fractions.attribute("id").as_uint() << " " << fractions.attribute("name").as_string() << " " << fractions.child_value() << std::endl;
				}
			}
		}
	}

	return fracs;
}
