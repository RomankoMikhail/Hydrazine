#ifndef MAINSTATE_HPP_
#define MAINSTATE_HPP_

#include "GameState.hpp"
#include "Button.hpp"

class MainState : public GameState {
	GUI::Button buttonResetSettings;
	GUI::Button buttonStartDemo;
	void startDemo();
public:
	virtual bool draw() const override;
	virtual bool update(const sf::Time & deltaTime) override;
	virtual bool handle(const sf::Event & event) override;

	MainState(GameStack & stack, GameContext & context);
};

#endif /* MAINSTATE_HPP_ */
