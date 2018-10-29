#ifndef SHIP_HPP_
#define SHIP_HPP_

#include <SFML/Graphics.hpp>
#include <map>

class Ship : public sf::Drawable, public sf::Transformable {
	sf::Sprite mSprite;

	//float currentShield, currentArmor;
	//float maxShield, maxArmor;
	std::string type;
	std::string name;
	unsigned maxHealth, currentHealth;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates state) const override;
public:
	void setTexture(const sf::Texture & texture);

	float getRotation() const;
	void setRotation(const float & angle);

	Ship() = default;
	virtual ~Ship() = default;
};

std::map<int, Ship> loadShips(std::string file);

#endif /* SHIP_HPP_ */
