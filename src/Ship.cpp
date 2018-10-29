#include "Ship.hpp"
#include <pugixml.hpp>

void Ship::draw(sf::RenderTarget & target, sf::RenderStates state) const {
	state.transform *= getTransform();

	target.draw(mSprite, state);
}

void Ship::setTexture(const sf::Texture & texture) {
	mSprite.setTexture(texture);
	mSprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

float Ship::getRotation() const {
	return mSprite.getRotation();
}

void Ship::setRotation(const float & angle) {
	mSprite.setRotation(angle);
}

std::map<int, Ship> loadShips(std::string file) {
	std::map<int, Ship> ships;

	pugi::xml_document doc;
	doc.load_file(file.c_str());
}
