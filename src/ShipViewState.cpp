#include "ShipViewState.hpp"

bool ShipViewState::draw() const {
	mContext.window->clear(sf::Color(0x1e, 0x1e, 0x1e));
	mContext.window->draw(mPlayerShip);
	mContext.window->draw(mButtonExit);
	mContext.window->draw(mButtonInventory);
	mContext.window->draw(mButtonMap);
	return true;
}

bool ShipViewState::update(const sf::Time & deltaTime) {
	mButtonExit.update(deltaTime);
	mButtonInventory.update(deltaTime);
	mButtonMap.update(deltaTime);
	return false;
}

bool ShipViewState::handle(const sf::Event & event) {
	mButtonExit.handle(event);
	mButtonInventory.handle(event);
	mButtonMap.handle(event);
	return false;
}

void ShipViewState::shutdown() {
	requestStackClear();
}

ShipViewState::ShipViewState(GameStack & stack, GameContext & context) :
		GameState(stack, context) {
	mPlayerShip.setTexture(context.textures.get("1_shuttle"));
	mPlayerShip.setPosition(context.settings.screen.width / 2.0f, context.settings.screen.height / 2.0f);

	mButtonExit.setText("Exit");
	mButtonExit.setSize(sf::Vector2i(80, 40));
	mButtonExit.setTextSize(30);
	mButtonExit.setSoundClick(context.sounds.get("button_click"));
	mButtonExit.setSoundOver(context.sounds.get("button_over"));
	mButtonExit.setFont(context.fonts.get("default"));
	mButtonExit.setPassiveColor(sf::Color(100, 100, 100));
	mButtonExit.setActiveColor(sf::Color(200, 100, 100));
	mButtonExit.setAlign(GUI::Center);
	mButtonExit.setCallback(std::bind(&ShipViewState::shutdown, this));
	mButtonExit.move(context.settings.screen.width - 100, context.settings.screen.height / 2 + 60);
	mButtonExit.setVolume(context.settings.audio.sfxVolume);

	mButtonInventory.setText("Inv.");
	mButtonInventory.setSize(sf::Vector2i(80, 40));
	mButtonInventory.setTextSize(30);
	mButtonInventory.setSoundClick(context.sounds.get("button_click"));
	mButtonInventory.setSoundOver(context.sounds.get("button_over"));
	mButtonInventory.setFont(context.fonts.get("default"));
	mButtonInventory.setPassiveColor(sf::Color(100, 100, 100));
	mButtonInventory.setActiveColor(sf::Color(100, 100, 200));
	mButtonInventory.setAlign(GUI::Center);
	//mButtonInventory.setCallback(std::bind(&Settings::defaultSettings, &(context.settings)));
	mButtonInventory.move(context.settings.screen.width - 100, context.settings.screen.height / 2);
	mButtonInventory.setVolume(context.settings.audio.sfxVolume);

	mButtonMap.setText("Map");
	mButtonMap.setSize(sf::Vector2i(80, 40));
	mButtonMap.setTextSize(30);
	mButtonMap.setSoundClick(context.sounds.get("button_click"));
	mButtonMap.setSoundOver(context.sounds.get("button_over"));
	mButtonMap.setFont(context.fonts.get("default"));
	mButtonMap.setPassiveColor(sf::Color(100, 100, 100));
	mButtonMap.setActiveColor(sf::Color(100, 100, 200));
	mButtonMap.setAlign(GUI::Center);
	//mButtonMap.setCallback(std::bind(&Settings::defaultSettings, &(context.settings)));
	mButtonMap.move(context.settings.screen.width - 100, context.settings.screen.height / 2 - 60);
	mButtonMap.setVolume(context.settings.audio.sfxVolume);
}
