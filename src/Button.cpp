#include "Button.hpp"

namespace GUI {

Button::Button() : mTextAlign(Left) {
	mFont = nullptr;
	// TODO Auto-generated constructor stub
}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

void Button::setOutlineColor(const sf::Color & color) {
	mShape.setOutlineColor(color);
}

void Button::setOutlineThickness(const float & thick) {
	mShape.setOutlineThickness(thick);
}

void Button::setPassiveColor(const sf::Color & color) {
	mPassive = color;
}

void Button::setActiveColor(const sf::Color & color) {
	mActive = color;
}

void Button::setSize(const sf::Vector2i & size) {
	mShape.setSize(sf::Vector2f(size.x, size.y));
	calcText();
}

void Button::setFont(const sf::Font & font) {
	mText.setFont(font);
	calcText();
}

void Button::setText(const sf::String & text) {
	mText.setString(text);
	calcText();
}

void Button::setAlign(const Align & align) {
	mTextAlign = align;
	calcText();
}

bool Button::isSelectable() const {
	return true;
}

void Button::handle(sf::Event & event) {
	if (event.type == sf::Event::MouseMoved) {
		sf::Vector2f pnt(event.mouseMove.x, event.mouseMove.y);
		if (getTransform().transformRect(mShape.getLocalBounds()).contains(
				pnt)) {
			select();
		} else {
			deselect();
		}
	}
}

//#include <iostream>

void Button::update(sf::Time deltaTime) {
	mEllapsed += deltaTime;
	float t = clamp(mEllapsed.asSeconds() / 0.25f, 0.0f, 1.0f);
	float r, g, b;

	r = mPrevious.r;
	g = mPrevious.g;
	b = mPrevious.b;

	if (mIsSelected) {
		r -= mActive.r;
		g -= mActive.g;
		b -= mActive.b;
	} else {
		r -= mPassive.r;
		g -= mPassive.g;
		b -= mPassive.b;
	}

	//r = clamp(r, -255.0f, 255.0f);
	//g = clamp(g, -255.0f, 255.0f);
	//b = clamp(b, -255.0f, 255.0f);

	r *= easeCubeInOut(t);
	g *= easeCubeInOut(t);
	b *= easeCubeInOut(t);

	//std::cout << easeCubeInOut(t) << std::endl;
	mShape.setFillColor(
			sf::Color(mPrevious.r - r, mPrevious.g - g, mPrevious.b - b));
}

void Button::calcText() {
	sf::Vector2f textLocalBounds(mText.getLocalBounds().width,
			mText.getLocalBounds().height);

	switch (mTextAlign) {
	case Left:
		mText.setPosition(0, ((mShape.getSize() - textLocalBounds) * 0.5f).y);
		break;
	case Center:
		mText.setPosition((mShape.getSize() - textLocalBounds) * 0.5f);
		break;
	case Right:
		mText.setPosition(mShape.getSize().x - textLocalBounds.x,
				((mShape.getSize() - textLocalBounds) * 0.5f).y);
		break;
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(mShape, states);
	target.draw(mText, states);
}

void Button::select() {
	if (!mIsSelected) {
		mPrevious = mShape.getFillColor();
		mEllapsed = sf::seconds(0);
		mIsSelected = true;
	}
}
void Button::deselect() {
	if (mIsSelected) {
		mPrevious = mShape.getFillColor();
		mEllapsed = sf::seconds(0);
		mIsSelected = false;
	}
}

}
/* namespace GUI */
