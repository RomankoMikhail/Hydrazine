#ifndef BEZIERCURVE_HPP_
#define BEZIERCURVE_HPP_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Utils.hpp"

class BezierCurve: public sf::Drawable {

	sf::Vector2f p0, p1, p2, p3, a, b, c;

	bool mIsBuild = false;
	float mLength = 0.0f;
	float mT = 0.0f;

public:
	const float & getLength() const {
		return mLength;
	}

	const bool & isBuild() const {
		return mIsBuild;
	}

	const sf::Vector2f & getP0() const {
		return p0;
	}
	const sf::Vector2f & getP1() const {
		return p1;
	}
	const sf::Vector2f & getP2() const {
		return p2;
	}
	const sf::Vector2f & getP3() const {
		return p3;
	}

	void build(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2,
			sf::Vector2f p3) {
		mT = 0.0f;

		this->p0 = p0;
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;

		c = 3.0f * (p1 - p0);
		b = 3.0f * (p2 - p1) - c;
		a = p3 - p0 - c - b;

		mIsBuild = true;

		mLength = 0;
		for (float i = 0.01f; i <= 1.001f; i += 0.01f) {
			mLength += VectorLen(getPoint(i) - getPoint(i - 0.01f));
		}
	}

	const float & getT() {
		return mT;
	}

	const float & advance(float distance) {
		for (int i = 0; i < 50; i++) {
			mT += (distance / 50.0f)
					/ (VectorLen(pow(mT, 2.0f) * a * 3.0f + mT * b * 2.0f + c));
			mT = clamp(mT, 0.0f, 1.0f);
		}
		return mT;
	}

	void append(BezierCurve otherCurve) {
		sf::Vector2f np0, np1, np2, np3;
		np0 = otherCurve.getP3();
		np1 = np0 + p1 - p0;
		np2 = np0 + p2 - p0;
		np3 = np0 + p3 - p0;
		build(np0, np1, np2, np3);
	}

	void connect(BezierCurve otherCurve) {
		sf::Vector2f np0, np1;
		np0 = otherCurve.getP3();
		np1 = np0 + p1 - p0;
		build(np0, np1, p2, p3);
	}

	void connectContinues(BezierCurve otherCurve) {
		sf::Vector2f np0, np1;
		np0 = otherCurve.getP3();
		np1 = (-(otherCurve.getP2() - np0)) + np0;
		build(np0, np1, p2, p3);
	}

	void appendContinues(BezierCurve otherCurve) {
		sf::Vector2f np0, np1, np2, np3;
		np0 = otherCurve.getP3();
		np1 = (-(otherCurve.getP2() - np0)) + np0;
		np2 = np0 + p2 - p0;
		np3 = np0 + p3 - p0;
		build(np0, np1, np2, np3);
	}

	sf::Vector2f getPoint(const float & t) const {
		float nt = clamp(t, 0.0f, 1.0f);
		return a * pow(nt, 3.0f) + b * pow(nt, 2.0f) + c * nt + p0;
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
			override {
		sf::RectangleShape box;

		box.setSize(sf::Vector2f(8, 8));
		box.setFillColor(sf::Color::Red);
		box.setOrigin(4, 4);

		box.setPosition(getPoint(0.0f));
		target.draw(box);
		for (float i = 0.1f; i <= 1.01f; i += 0.1f) {
			box.setPosition(getPoint(i));
			target.draw(box);
			drawLine(getPoint(i - 0.1f), getPoint(i), sf::Color::Red, target,
					states);
		}

		box.setFillColor(sf::Color::Green);

		drawLine(p0, p1, sf::Color::Green, target, states);
		box.setPosition(p1);
		target.draw(box);

		drawLine(p3, p2, sf::Color::Green, target, states);
		box.setPosition(p2);
		target.draw(box);
	}
};

#endif /* BEZIERCURVE_HPP_ */
