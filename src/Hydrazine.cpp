#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <cmath>

#define PI 3.14159265

using namespace std;
using namespace sf;

#include "Utils.hpp"
#include "BezierCurve.hpp"

float sine_ease_in_out(float f) {
	return float(0.5) * (float(1.0) - cos(f * PI));
}

class Ship {
private:
	BezierCurve mCurve;
	float mCurvePos;
	float mSpeed;
	Time mEllapsed;
public:
	Sprite mSprite;

	Ship() {
		mCurvePos = 0;
		mSpeed = 0;
	}

	const BezierCurve & getPathCurve() const {
		return mCurve;
	}

	void setTargetPosition(Vector2f position, float speed) {
		mSpeed = speed;
		mEllapsed = seconds(0);
		if(!mCurve.isBuild() || mCurve.getT() >= 1.0f) {
			mCurve.build(	mSprite.getPosition(),
							mSprite.getPosition() + VectorNormilize(position - mSprite.getPosition()) * 10.f,
							position + VectorNormilize(mSprite.getPosition() - position) * 10.f,
							position);
		} else {
			Vector2f p1, p2, p3, p4;
			// Fix for compiler stupidity
			p1 = mCurve.getPoint(mCurve.getT());
			p2 = mCurve.getPoint(mCurve.advance(speed));
			p3 = position + VectorNormilize(mSprite.getPosition() - position) * 10.f;
			p4 = position;
			mCurve.build(p1, p2, p3, p4);
		}
	}

	void update(Time delta) {
		if(mCurve.isBuild()) {
			mEllapsed += delta;
			mSprite.setPosition(mCurve.getPoint(mCurve.advance(mSpeed * delta.asSeconds())));
		}
	}
};

int main() {
	RenderWindow window(VideoMode(1280, 720), "Hydrazine");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	Texture logo, ship;
	logo.loadFromFile("images/logo.png");
	ship.loadFromFile("images/ship.png");

	Ship mship;
	mship.mSprite.setTexture(ship);
	mship.mSprite.setOrigin(12, 12);
	Sprite logoSprite;
	logoSprite.setTexture(logo);
	logoSprite.setColor(Color(255, 255, 255, 128));
	//mship.setTargetPosition(Vector2f(0, 0), 15);

	Clock timer;

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::MouseButtonPressed) {
				mship.setTargetPosition(
						Vector2f(event.mouseButton.x, event.mouseButton.y), 50);
			}
		}
		window.clear(Color(0x1a, 0x1a, 0x1a));
		mship.update(timer.restart());
		//window.draw(mship.getPathCurve());
		window.draw(mship.mSprite);
		window.draw(logoSprite);
		window.display();

	}

	return 0;
}
