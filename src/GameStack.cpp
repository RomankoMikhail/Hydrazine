#include "GameStack.h"

void GameStack::update(const sf::Time & deltaTime) {
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
		if ((*itr)->update(deltaTime) == false)
			break;
	}
	applyPendingChanges();
}

void GameStack::draw() const {
	for (auto itr = mStack.begin(); itr != mStack.end(); ++itr) {
		if ((*itr)->draw() == false)
			break;
	}
}

void GameStack::handleEvent(const sf::Event & event) {
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
		if ((*itr)->handle(event) == false)
			break;
	}
	applyPendingChanges();
}

void GameStack::pushState(const States::ID & state) {
	mPendingList.push_back(PendingChange(Push, state));
}

void GameStack::popState() {
	mPendingList.push_back(PendingChange(Pop));
}

void GameStack::clearStates() {
	mPendingList.push_back(PendingChange(Clear));
}

bool GameStack::isEmpty() const {
	return mStack.size() == 0;
}

GameState::Ptr GameStack::createState(const States::ID & state) {
	assert(state != States::None);
	auto found = mFactories.find(state);
	assert(found != mFactories.end());

	return found->second();
}

void GameStack::applyPendingChanges() {
	for (PendingChange change : mPendingList) {
		switch (change.action) {
		case Push:
			mStack.push_back(createState(change.stateID));
			break;

		case Pop:
			mStack.pop_back();
			break;

		case Clear:
			mStack.clear();
			break;
		}
	}

	mPendingList.clear();
}

GameStack::GameStack(GameContext context) :
		mContext(context) {
}

GameStack::PendingChange::PendingChange(Action action, States::ID stateID) {
	this->stateID = stateID;
	this->action = action;
}
