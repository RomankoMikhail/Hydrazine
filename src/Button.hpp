#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "Easing.hpp"
#include "Utils.hpp"
#include <functional>
#include "Component.hpp"

namespace GUI {

enum Align {
	Left, Center, Right
};

class Button: public Component {
	sf::Color mPassive, mActive, mPrevious;
	sf::RectangleShape mShape;
	sf::Font * mFont;
	sf::Text mText;
	sf::Time mEllapsed;

	Align mTextAlign;

	std::function<void(void)> mCallback;

	void calcText();
public:

	void setPassiveColor(const sf::Color & color);
	void setActiveColor(const sf::Color & color);
	void setSize(const sf::Vector2i & size);
	void setFont(const sf::Font & font);
	void setText(const sf::String & text);
	void setAlign(const Align & align);
	void setOutlineColor(const sf::Color & color);
	void setOutlineThickness(const float & thick);

	virtual void select() override;
	virtual void deselect() override;
	virtual bool isSelectable() const override;
	virtual void handle(sf::Event & event) override;
	virtual void update(sf::Time deltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
			override;

	Button();
	virtual ~Button();
};

} /* namespace GUI */

#endif /* BUTTON_HPP_ */
