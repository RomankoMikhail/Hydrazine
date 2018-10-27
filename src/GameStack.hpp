#ifndef GAMESTACK_HPP_
#define GAMESTACK_HPP_

#include <memory>
#include <functional>
#include <map>
#include <vector>
#include <cassert>
#include "defs.hpp"
#include "GameState.hpp"

class GameStack {
private:
	enum Action {
		Push, Pop, Clear
	};

	struct PendingChange {
		PendingChange(Action action, States::ID stateID = States::None);

		Action action;
		States::ID stateID;
	};

public:
	explicit GameStack(GameContext context);

	template<typename T>
	void registerState(States::ID state);

	void update(const sf::Time & deltaTime);
	void draw() const;
	void handle(const sf::Event & event);

	void pushState(const States::ID & state);
	void popState();
	void clearStates();

	bool isEmpty() const;
private:

	GameState::Ptr createState(const States::ID & state);
	void applyPendingChanges();

	std::map<States::ID, std::function<GameState::Ptr()>> mFactories;
	GameContext mContext;
	std::vector<GameState::Ptr> mStack;
	std::vector<PendingChange> mPendingList;
};

template<typename T>
void GameStack::registerState(States::ID state) {
	mFactories[state] = [this] ()
	{
		return GameState::Ptr(new T(*this, mContext));
	};
}

#endif /* GAMESTACK_HPP_ */
