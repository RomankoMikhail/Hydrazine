#ifndef SHIPVIEWSTATE_HPP_
#define SHIPVIEWSTATE_HPP_

#include "GameState.hpp"

class ShipViewState : public GameState {
public:
	virtual bool draw() const override;
	virtual bool update(const sf::Time & deltaTime) override;
	virtual bool handle(const sf::Event & event) override;

	ShipViewState(GameStack & stack, GameContext & context);
};

#endif /* SHIPVIEWSTATE_HPP_ */
