#include "GameState.hpp"

GameContext::GameContext(Settings & setting, sf::RenderWindow & window, ResourceManager<sf::Font, sf::String> & font,
		ResourceManager<sf::Texture, sf::String> & texture, ResourceManager<sf::SoundBuffer, sf::String> & sound) :
		settings(setting), fonts(font), textures(texture), sounds(sound) {
	this->window = &window;
}


void GameState::requestStackPush(const States::ID & state) {
	mStack->pushState(state);
}

void GameState::requestStackPop() {
	mStack->popState();
}

void GameState::requestStackClear() {
	mStack->clearStates();
}

GameState::GameState(GameStack & stack, GameContext & context) :
		mContext(context) {
	mStack = &stack;
}
