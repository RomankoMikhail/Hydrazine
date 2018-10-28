#include "SettingsState.hpp"

bool SettingsState::draw() const {
	mContext.window->draw(buttonResetSettings);
	return true;
}

bool SettingsState::update(const sf::Time & deltaTime) {
	buttonResetSettings.update(deltaTime);
	return true;
}

bool SettingsState::handle(const sf::Event & event) {
	buttonResetSettings.handle(event);
	return false;
}

SettingsState::SettingsState(GameStack & stack, GameContext & context) :
		GameState(stack, context) {
	buttonResetSettings.setText("Reset Settings");
	buttonResetSettings.setSize(sf::Vector2i(200, 40));
	buttonResetSettings.setTextSize(30);
	buttonResetSettings.setSoundClick(context.sounds.get("button_click"));
	buttonResetSettings.setSoundOver(context.sounds.get("button_over"));
	buttonResetSettings.setFont(context.fonts.get("default"));
	buttonResetSettings.setPassiveColor(sf::Color(100, 100, 100));
	buttonResetSettings.setActiveColor(sf::Color(100, 100, 200));

	buttonResetSettings.setCallback(std::bind(&Settings::defaultSettings, &(context.settings)));

}
