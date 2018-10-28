#include "Button.hpp"

namespace GUI {

Button::Button() :
		mTextAlign(Left) {
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

void Button::handle(const sf::Event & event) {
	sf::Vector2f point;

	switch (event.type) {
	case sf::Event::MouseMoved:
		point.x = event.mouseMove.x;
		point.y = event.mouseMove.y;
		if (getTransform().transformRect(mShape.getLocalBounds()).contains(point)) {
			select();
		} else {
			deselect();
		}
		break;
	case sf::Event::MouseButtonPressed:
		point.x = event.mouseButton.x;
		point.y = event.mouseButton.y;
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (getTransform().transformRect(mShape.getLocalBounds()).contains(point)) {
				mSoundClick.play();
				activate();
			}
		}
		break;
	default:
		break;
	}
}

void Button::update(const sf::Time & deltaTime) {
	mEllapsed += deltaTime;
	float t = clamp(mEllapsed.asSeconds() / 0.15f, 0.0f, 1.0f);
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

	r *= easeCubeInOut(t);
	g *= easeCubeInOut(t);
	b *= easeCubeInOut(t);

	mShape.setFillColor(sf::Color(mPrevious.r - r, mPrevious.g - g, mPrevious.b - b));
}

void Button::calcText() {
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

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(mShape, states);
	target.draw(mText, states);
}

void Button::select() {
	if (!mIsSelected) {
		mSoundOver.play();
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

void Button::setCallback(std::function<void(void)> callback) {
	mCallback = callback;
}

void Button::activate() {
	if (mCallback)
		mCallback();
}
void Button::deactivate() {

}

void Button::setTextColor(const sf::Color & color) {
	mText.setFillColor(color);
}

void Button::setTextSize(const int & size) {
	mText.setCharacterSize(size);
	calcText();
}

void Button::setTextStyle(const unsigned & style) {
	mText.setStyle(style);
	calcText();
}

void Button::setSoundOver(const sf::SoundBuffer & buf) {
	mSoundOver.setBuffer(buf);
}

void Button::setSoundClick(const sf::SoundBuffer & buf) {
	mSoundClick.setBuffer(buf);
}

void Button::setVolume(const float & volume) {
	mSoundClick.setVolume(volume);
	mSoundOver.setVolume(volume);
}

}
/* namespace GUI */
