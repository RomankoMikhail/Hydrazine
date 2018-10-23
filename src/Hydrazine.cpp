#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace sf;

template<typename T>
float VectorLen(Vector2<T> vec) {
	return hypot(vec.x, vec.y);
}

template<typename T>
Vector2<T> VectorNormilize(Vector2<T> vec) {
	float length = VectorLen(vec);
	if(length == 0.0f)
		return vec;
	return Vector2<T>(vec.x / length, vec.y / length);
}

template<typename T>
T clamp(const T & value, const T & lower, const T & upper) {
	return min(max(value, lower), upper);
}

template<typename T>
ostream & operator<<(ostream & stream, Vector2<T> vector) {
	stream << vector.x << ' ' << vector.y;
}

template<typename T>
class BezierCurve2 {
public:
	Vector2<T> p0, p1, p2;

	BezierCurve2() {
		p0 = p1 = p2 = Vector2<T>(0, 0);
	}

	T length() {
		Vector2<T> a, b;

		if(p0 == p1 || p1 == p2) {
			return VectorLen(p0 - p2);
		}

		a.x = p0.x - 2 * p1.x + p2.x;
		a.y = p0.y - 2 * p1.y + p2.y;
		b.x = 2 * p1.x - 2 * p0.x;
		b.y = 2 * p1.y - 2 * p0.y;
		float A = 4 * (a.x * a.x + a.y * a.y);
		float B = 4 * (a.x * b.x + a.y * b.y);
		float C = b.x * b.x + b.y * b.y;

		float Sabc = 2 * sqrt(A + B + C);
		float A_2 = sqrt(A);
		float A_32 = 2 * A * A_2;
		float C_2 = 2 * sqrt(C);
		float BA = B / A_2;

		return (A_32 * Sabc + A_2 * B * (Sabc - C_2) + (4 * C * A - B * B) * log((2 * A_2 + BA + Sabc) / (BA + C_2)))
				/ (4 * A_32);
	}

	Vector2<T> getPoint(float t) {
		t = clamp<float>(t, 0, 1);
		return pow(1 - t, 2) * p0 + 2 * t * (1 - t) * p1 + t * t * p2;
	}

	Vector2<T> getSpeed(float t) {
		t = clamp<float>(t, 0, 1);
		return 2 * (1 - t) * (p1 - p0) + 2 * t * (p2 - p1);
	}
};

float sine_ease_in_out(float f) {
	return float(0.5) * (float(1.0) - cos(f * M_PI));
}

float kP = 0.6f, kI = 0.f, kD = 0.f;

class Ship {
private:
	Vector2f targetPosition, previousTargetPosition;
	Vector2f currentSpeed;
	//BezierCurve2<float> mCurve;
	Time mElapsedTime, mTotalTime;
public:
	Sprite mSprite;
	Ship() {
		currentSpeed = Vector2f(0, 0);
	}

	void setTargetPosition(Vector2f position, float speed) {
		targetPosition = position;
	}

	void update(Time delta) {
		Vector2f error, errorPrevious, output;
		Vector2f integral, derivative;

		errorPrevious = error;
		error = VectorNormilize(targetPosition - mSprite.getPosition());
		integral = integral + error * delta.asSeconds();
		derivative = (error - errorPrevious) / delta.asSeconds();
		output = kP * error + kI * integral + kD * derivative;

		currentSpeed += (output * 0.000001f);
		if (VectorLen(currentSpeed) > 1000.f) {
			currentSpeed = VectorNormilize(currentSpeed) * 50.f;
		}


		mSprite.move(currentSpeed * delta.asSeconds());


		/*float appliedSpeed = min(speed, VectorLen(mSprite.getPosition() - targetPosition));
		 mSprite.move(VectorNormilize(targetPosition - mSprite.getPosition()) * appliedSpeed * delta.asSeconds());*/
	}
};

int main() {
	RenderWindow window(VideoMode(1280, 720), "Hydrazine");
	Texture logo, ship;
	logo.loadFromFile("images/logo.png");
	ship.loadFromFile("images/ship.png");

	Ship mship;
	mship.mSprite.setTexture(ship);
	Sprite logoSprite;
	logoSprite.setTexture(logo);
	//mship.setTargetPosition(Vector2f(100, 100), 15);

	Clock timer;

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::MouseButtonPressed) {
				mship.setTargetPosition(Vector2f(event.mouseButton.x, event.mouseButton.y), 50);
			}
		}
		window.clear(Color(0x1a, 0x1a, 0x1a));
		mship.update(timer.restart());
		window.draw(mship.mSprite);
		window.draw(logoSprite);
		window.display();

	}

	return 0;
}
