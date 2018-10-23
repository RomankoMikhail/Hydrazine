#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <cmath>

#define PI 3.14159265

using namespace std;
using namespace sf;

template<typename T>
float VectorLen(Vector2<T> vec) {
	return hypot(vec.x, vec.y);
}

template<typename T>
Vector2<T> VectorNormilize(Vector2<T> vec) {
	float length = VectorLen(vec);
	if (length == 0.0f)
		return vec;
	return Vector2<T>(vec.x / length, vec.y / length);
}

template<typename T>
T clamp(const T & value, const T & lower, const T & upper) {
	return min(max(value, lower), upper);
}

template<typename T>
ostream & operator<<(ostream & stream, Vector2<T> vector) {
	return stream << vector.x << ' ' << vector.y;
}

class BezierCurve: public sf::Drawable {

	Vector2f p0, p1, p2, p3, a, b, c;
	Vector2f v1, v2, v3;

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

	const Vector2f & getP0() const {
		return p0;
	}
	const Vector2f & getP1() const {
		return p1;
	}
	const Vector2f & getP2() const {
		return p2;
	}
	const Vector2f & getP3() const {
		return p3;
	}

	void build(Vector2f p0, Vector2f p1, Vector2f p2, Vector2f p3) {
		cout << p0 << endl;
		cout << p1 << endl;
		cout << p2 << endl;
		cout << p3 << endl;
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
		for(float i = 0.001f; i <= 1.0001f; i += 0.001f)
		{
			mLength += VectorLen(getPoint(i) - getPoint(i - 0.001f));
		}
		cout << "Curve length:" << mLength << endl;

		v1 = -3.0f * p0 + 9.0f * p1 - 9.0f * p2 + 3.0f * p3;
		v2 = 6.0f * p0 - 12.0f * p1 + 6.0f * p2;
		v3 = -3.0f * p0 + 3.0f * p1;
	}

	const float & getT() {
		return mT;
	}

	const float & advance(float distance) {
		mT += distance / (VectorLen(pow(mT, 2.0f) * v1 + mT * v2 + v3));

		mT = clamp(mT, 0.0f, 1.0f);
		return mT;
	}

	void append(BezierCurve otherCurve) {
		Vector2f np0, np1, np2, np3;
		np0 = otherCurve.getP3();
		np1 = np0 + p1 - p0;
		np2 = np0 + p2 - p0;
		np3 = np0 + p3 - p0;
		build(np0, np1, np2, np3);
	}

	void connect(BezierCurve otherCurve) {
		Vector2f np0, np1;
		np0 = otherCurve.getP3();
		np1 = np0 + p1 - p0;
		build(np0, np1, p2, p3);
	}

	void connectContinues(BezierCurve otherCurve) {
		Vector2f np0, np1;
		np0 = otherCurve.getP3();
		np1 = (-(otherCurve.getP2() - np0)) + np0;
		build(np0, np1, p2, p3);
	}

	void appendContinues(BezierCurve otherCurve) {
		Vector2f np0, np1, np2, np3;
		np0 = otherCurve.getP3();
		np1 = (-(otherCurve.getP2() - np0)) + np0;
		np2 = np0 + p2 - p0;
		np3 = np0 + p3 - p0;
		build(np0, np1, np2, np3);
	}

	Vector2f getPoint(const float & t) const {
		float nt = clamp(t, 0.0f, 1.0f);
		return a * pow(nt, 3.0f) + b * pow(nt, 2.0f) + c * nt + p0;
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
			override {
		sf::Vertex line[] = { sf::Vertex(p0), sf::Vertex(p1) };

		RectangleShape box;
		box.setSize(Vector2f(8, 8));
		box.setFillColor(Color::Red);
		box.setOrigin(4, 4);

		line[0].color = Color::Red;
		line[1].color = Color::Red;
		box.setPosition(getPoint(0.0f));
		target.draw(box);
		for (float i = 0.1f; i <= 1.01f; i += 0.1f) {
			line[0].position = getPoint(i - 0.1f);
			line[1].position = getPoint(i);
			box.setPosition(line[1].position);
			target.draw(box);
			target.draw(line, 2, sf::Lines);
		}

		box.setFillColor(Color::Green);
		line[0].color = Color::Green;
		line[1].color = Color::Green;
		line[0].position = p0;
		line[1].position = p1;
		target.draw(line, 2, sf::Lines);
		box.setPosition(line[1].position);
		target.draw(box);

		line[0].position = p3;
		line[1].position = p2;
		target.draw(line, 2, sf::Lines);
		box.setPosition(line[1].position);
		target.draw(box);
	}
};

class Ship {
private:
	BezierCurve mCurve;
	float mCurvePos;
	float mSpeed;
public:
	Sprite mSprite;

	Ship() {
		mCurvePos = 0;
		mSpeed = 0;
		//mSprite.setOrigin(24, 24);
	}

	const BezierCurve & getPathCurve() const {
		return mCurve;
	}

	void setTargetPosition(Vector2f position, float speed) {
		mSpeed = speed;
		if(!mCurve.isBuild() || mCurve.getT() >= 1.0f) {
			mCurve.build(	mSprite.getPosition(),
							mSprite.getPosition() + VectorNormilize(position - mSprite.getPosition()) * speed,
							position + VectorNormilize(mSprite.getPosition() - position) * speed,
							position);
		} else {
			mCurve.build(	mCurve.getPoint(mCurve.getT()),
							mCurve.getPoint(mCurve.advance(speed)),
							position + VectorNormilize(mSprite.getPosition() - position) * speed,
							position);
		}
	}

	void update(Time delta) {
		if(mCurve.isBuild()) {
			//mCurvePos += delta.asSeconds() / (mCurve.getLength() / mSpeed);
			mSprite.setPosition(mCurve.getPoint(mCurve.advance(mSpeed * delta.asSeconds())));
		}

		/*float appliedSpeed = min(speed, VectorLen(mSprite.getPosition() - targetPosition));
		 mSprite.move(VectorNormilize(targetPosition - mSprite.getPosition()) * appliedSpeed * delta.asSeconds());*/
	}
};

int main() {
	RenderWindow window(VideoMode(1280, 720), "Hydrazine");
	window.setFramerateLimit(30);
	window.setVerticalSyncEnabled(true);
	Texture logo, ship;
	logo.loadFromFile("images/logo.png");
	ship.loadFromFile("images/ship.png");

	Ship mship;
	mship.mSprite.setTexture(ship);
	Sprite logoSprite;
	logoSprite.setTexture(logo);
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
		window.draw(mship.getPathCurve());
		window.draw(mship.mSprite);
		window.draw(logoSprite);
		window.display();

	}

	return 0;
}
