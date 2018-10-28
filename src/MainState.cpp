#include "MainState.hpp"

bool MainState::draw() const {
	mContext.window->clear();

	mContext.window->draw(buttonResetSettings);
	mContext.window->draw(buttonStartDemo);
	return true;
}

bool MainState::update(const sf::Time & deltaTime) {
	buttonResetSettings.update(deltaTime);
	buttonStartDemo.update(deltaTime);
	return true;
}

bool MainState::handle(const sf::Event & event) {
	buttonResetSettings.handle(event);
	buttonStartDemo.handle(event);
	return false;
}

void MainState::startDemo() {
	requestStackPop();
	requestStackPush(States::ShipView);
}

MainState::MainState(GameStack & stack, GameContext & context) :
		GameState(stack, context) {
	buttonResetSettings.setText("Reset Settings");
	buttonResetSettings.setSize(sf::Vector2i(300, 40));
	buttonResetSettings.setTextSize(30);
	buttonResetSettings.setSoundClick(context.sounds.get("button_click"));
	buttonResetSettings.setSoundOver(context.sounds.get("button_over"));
	buttonResetSettings.setFont(context.fonts.get("default"));
	buttonResetSettings.setPassiveColor(sf::Color(100, 100, 100));
	buttonResetSettings.setActiveColor(sf::Color(100, 100, 200));
	buttonResetSettings.setAlign(GUI::Center);
	buttonResetSettings.setCallback(std::bind(&Settings::defaultSettings, &(context.settings)));
	buttonResetSettings.move(context.settings.screen.width / 2, context.settings.screen.height / 2);
	buttonResetSettings.setVolume(context.settings.audio.sfxVolume);

	buttonStartDemo.setText("Start Demo");
	buttonStartDemo.setSize(sf::Vector2i(300, 40));
	buttonStartDemo.setTextSize(30);
	buttonStartDemo.setSoundClick(context.sounds.get("button_click"));
	buttonStartDemo.setSoundOver(context.sounds.get("button_over"));
	buttonStartDemo.setFont(context.fonts.get("default"));
	buttonStartDemo.setPassiveColor(sf::Color(100, 100, 100));
	buttonStartDemo.setActiveColor(sf::Color(100, 100, 200));
	buttonStartDemo.setAlign(GUI::Center);
	buttonStartDemo.setCallback(std::bind(&MainState::startDemo, this));
	buttonStartDemo.move(context.settings.screen.width / 2, context.settings.screen.height / 2 + 60);
	buttonStartDemo.setVolume(context.settings.audio.sfxVolume);
}
