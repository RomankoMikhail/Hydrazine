#include "GameStack.h"

void GameStack::State::init() {

}

GameStack::State::State(GameStack * stack) {
	mStack = stack;
}

void GameStack::State::draw(sf::RenderTarget & target, sf::RenderStates state) const {
	// ...
}

void GameStack::State::update(const sf::Time delta) {
	// ...
}

const bool GameStack::State::isDrawBreak() const {
	return true;
}

const bool GameStack::State::isUpdateBreak() const {
	return true;
}

void GameStack::draw(sf::RenderTarget & target, sf::RenderStates state) const {
	auto iter = mStack.rbegin();
	for(; iter != mStack.rend(); ++iter) {
		target.draw(**iter);
		if((*iter)->isDrawBreak())
			break;
	}
}

void GameStack::update(const sf::Time delta) {
	auto stackIter = mStack.begin();
	for(; stackIter != mStack.end(); ++stackIter) {
		(*stackIter)->update(delta);
		if((*stackIter)->isUpdateBreak())
			break;
	}

	auto actionIter = mActions.begin();
	for(; actionIter != mActions.end(); ++actionIter) {
		if(actionIter->action == Action::POP) {
			mStack.pop_back();
		} else {
			mStack.push_back(actionIter->obj);
		}
	}
}

void GameStack::pop() {
	Action act;
	act.action = act.POP;
	mActions.push_back(act);
}

void GameStack::push(std::shared_ptr<State> state) {
	Action act;
	act.action = act.PUSH;
	act.obj = state;
	mActions.push_back(act);
}
