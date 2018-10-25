#include "GameState.h"

GameContext::GameContext(sf::RenderWindow & window) {
	this->window = &window;
}


void GameState::requestStackPush(const States::ID & state)
{
	mStack->pushState(state);
}

void GameState::requestStackPop()
{
	mStack->popState();
}

void GameState::requestStackClear()
{
	mStack->clearStates();
}

GameState::GameState(GameStack & stack, GameContext & context)
: mContext(context) {
	mStack = &stack;
}
