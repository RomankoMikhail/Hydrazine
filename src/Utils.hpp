#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

template<typename T>
float VectorLen(sf::Vector2<T> vec) {
	return std::hypot(vec.x, vec.y);
}

template<typename T>
sf::Vector2<T> VectorNormilize(sf::Vector2<T> vec) {
	float length = VectorLen(vec);
	if (length == 0.0f)
		return vec;
	return sf::Vector2<T>(vec.x / length, vec.y / length);
}

template<typename T>
T clamp(const T & value, const T & lower, const T & upper) {
	return std::min(std::max(value, lower), upper);
}

template<typename T>
std::ostream & operator<<(std::ostream & stream, sf::Vector2<T> vector) {
	return stream << vector.x << ' ' << vector.y;
}

template<typename T>
void drawLine(sf::Vector2<T> pos1, sf::Vector2<T> pos2, sf::Color color, sf::RenderTarget& target, sf::RenderStates states)
{
	sf::Vertex line[] = { sf::Vertex(pos1, color), sf::Vertex(pos2, color) };
	target.draw(line, 2, sf::Lines, states);
}
#endif /* UTILS_HPP_ */
