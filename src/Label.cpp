#include "Label.hpp"

namespace GUI {

void Label::calcText() {
	sf::Vector2f textLocalBounds(mText.getLocalBounds().width, mText.getLocalBounds().height);
	sf::FloatRect textBound = mText.getLocalBounds();
	mText.setOrigin(textBound.left + textBound.width / 2.f, textBound.top + textBound.height / 2.f);

	switch (mTextAlign) {
	case Left:
		mText.setPosition(textLocalBounds.x / 2.0f, mShape.getSize().y / 2.0f);
		break;
	case Center:
		mText.setPosition(mShape.getSize().x / 2.0f, mShape.getSize().y / 2.0f);
		break;
	case Right:
		mText.setPosition(mShape.getSize().x - textLocalBounds.x / 2.0f, mShape.getSize().y / 2.0f);
		break;
	}
}

void Label::setFillColor(const sf::Color & color) {
	mShape.setFillColor(color);
}

void Label::setSize(const sf::Vector2i & size) {
	mShape.setSize(sf::Vector2f(size.x, size.y));
}

void Label::setFont(const sf::Font & font) {
	mText.setFont(font);
}

void Label::setAlign(const Align & align) {
	mTextAlign = align;
}

void Label::setOutlineColor(const sf::Color & color) {
	mShape.setOutlineColor(color);
}

void Label::setOutlineThickness(const float & thick) {
	mShape.setOutlineThickness(thick);
}

void Label::setText(const sf::String & text) {
	mText.setString(text);
}

void Label::setTextColor(const sf::Color & color) {
	mText.setFillColor(color);
}

void Label::setTextSize(const int & size) {
	mText.setCharacterSize(size);
}

void Label::setTextStyle(const unsigned & style) {
	mText.setStyle(style);
}

bool Label::isSelectable() const {
	return false;
}

void Label::handle(const sf::Event & event) {
	return;
}

void Label::update(const sf::Time & deltaTime) {
	return;
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(mShape, states);
	target.draw(mText, states);
}

Label::Label() :
		mTextAlign(Left) {

}
}
