#ifndef SHIP_HPP_
#define SHIP_HPP_

#include <SFML/Graphics.hpp>

class Ship : public sf::Drawable, public sf::Transformable {
	sf::Sprite mSprite;

	//float currentShield, currentArmor;
	//float maxShield, maxArmor;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates state) const override;
public:
	void setTexture(const sf::Texture & texture);

	float getRotation() const;
	void setRotation(const float & angle);

	Ship() = default;
	virtual ~Ship() = default;
};

#endif /* SHIP_HPP_ */
