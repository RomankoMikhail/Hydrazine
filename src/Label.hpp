#ifndef LABEL_HPP_
#define LABEL_HPP_

#include "Component.hpp"
#include "Button.hpp"

namespace GUI {

class Label: public Component {
	sf::RectangleShape mShape;
	sf::Text mText;

	Align mTextAlign;

	void calcText();
public:

	void setFillColor(const sf::Color & color);
	void setSize(const sf::Vector2i & size);
	void setFont(const sf::Font & font);

	void setAlign(const Align & align);

	void setOutlineColor(const sf::Color & color);
	void setOutlineThickness(const float & thick);

	void setText(const sf::String & text);
	void setTextColor(const sf::Color & color);
	void setTextSize(const int & size);
	void setTextStyle(const unsigned & style);

	virtual bool isSelectable() const override;
	virtual void handle(const sf::Event & event) override;
	virtual void update(const sf::Time & deltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Label();
	virtual ~Label() = default;
};

} /* namespace GUI */

#endif /* LABEL_HPP_ */
