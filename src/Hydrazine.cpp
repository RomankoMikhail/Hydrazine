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
#include "Easing.hpp"

#include "GameStack.h"
#include "GameState.h"




class MainMenuState: public GameState {
	RectangleShape rect;
public:
	MainMenuState(GameStack & stack, GameContext & context) :
			GameState(stack, context) {
		rect.setFillColor(sf::Color::Red);
		rect.setSize(sf::Vector2f(200, 300));
	}
	virtual ~MainMenuState() = default;

	virtual bool draw() const {
		mContext.window->draw(rect);
		return false;
	}
	virtual bool update(const sf::Time & deltaTime) {
		return false;
	}
	virtual bool handle(const sf::Event & event) {
		return false;
	}
};

/*
 GameStack gstack;

 class MainState : public GameStack::State {
 RectangleShape rect;
 virtual void init() override {
 rect.setFillColor(Color::Cyan);
 rect.setSize(Vector2f(200, 400));
 }

 virtual void draw(sf::RenderTarget & target, sf::RenderStates state) const override {
 target.draw(rect);
 }
 public:
 };*/
/*
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
		if (!mCurve.isBuild() || mCurve.getT() >= 1.0f) {
			mCurve.build(mSprite.getPosition(),
					mSprite.getPosition()
							+ VectorNormilize(position - mSprite.getPosition())
									* 10.f,
					position
							+ VectorNormilize(mSprite.getPosition() - position)
									* 10.f, position);
		} else {
			Vector2f p1, p2, p3, p4;
			// Fix for compiler stupidity
			p1 = mCurve.getPoint(mCurve.getT());
			p2 = mCurve.getPoint(mCurve.advance(speed));
			p3 = position
					+ VectorNormilize(mSprite.getPosition() - position) * 10.f;
			p4 = position;
			mCurve.build(p1, p2, p3, p4);
		}
	}

	void update(Time delta) {
		if (mCurve.isBuild()) {
			mEllapsed += delta;
			mSprite.setPosition(
					mCurve.getPoint(
							mCurve.advance(mSpeed * delta.asSeconds())));
		}
	}
};*/

int main() {
	RenderWindow window(VideoMode(1280, 720), "Hydrazine");



	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	Texture logo, ship;
	logo.loadFromFile("images/logo.png");
	ship.loadFromFile("images/ship.png");
	GameStack gStack = GameStack(GameContext(window));

	gStack.registerState<MainMenuState>(States::Main);
	gStack.pushState(States::Main);

	//Ship mship;
	//mship.mSprite.setTexture(ship);
	//mship.mSprite.setOrigin(12, 12);
	Sprite logoSprite;
	logoSprite.setTexture(logo);
	logoSprite.setColor(Color(255, 255, 255, 128));
	//mship.setTargetPosition(Vector2f(0, 0), 15);
	float t = 0;

	RectangleShape s;
	s.setSize(Vector2f(100, 200));
	s.setFillColor(Color::Yellow);
	s.setOrigin(50, 100);
	s.setPosition(300, 300);
	Clock timer;

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			gStack.handleEvent(event);
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::MouseButtonPressed) {
				//mship.setTargetPosition(
						//Vector2f(event.mouseButton.x, event.mouseButton.y), 50);
			}
			if (event.type == Event::KeyPressed) {
				t = 0;
			}
		}
		window.clear(Color(0x1a, 0x1a, 0x1a));
		gStack.draw();
		gStack.update(timer.getElapsedTime());
		//mship.update(timer.restart());
		//window.draw(mship.getPathCurve());
		t += 0.005f;
		t = clamp(t, 0.0f, 1.0f);
		s.setRotation(easeSineInOut(t) * 45);

		//window.draw(mship.mSprite);
		window.draw(logoSprite);
		window.draw(s);
		window.display();

	}

	return 0;
}
