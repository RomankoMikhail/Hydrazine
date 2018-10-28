#ifndef SETTINGSSTATE_HPP_
#define SETTINGSSTATE_HPP_

#include "GameState.hpp"
#include "Button.hpp"

class SettingsState : public GameState {
	GUI::Button buttonResetSettings;
public:
	virtual bool draw() const override;
	virtual bool update(const sf::Time & deltaTime) override;
	virtual bool handle(const sf::Event & event) override;

	SettingsState(GameStack & stack, GameContext & context);
};

#endif /* SETTINGSSTATE_HPP_ */
