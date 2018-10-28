#include "ShipViewState.hpp"

bool ShipViewState::draw() const {
	mContext.window->clear(sf::Color(0x1e, 0x1e, 0x1e));

	return true;
}

bool ShipViewState::update(const sf::Time & deltaTime) {
	return true;
}

bool ShipViewState::handle(const sf::Event & event) {
	return false;
}

ShipViewState::ShipViewState(GameStack & stack, GameContext & context) :
		GameState(stack, context) {
}
