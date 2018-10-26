#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <memory>
#include <SFML/Graphics.hpp>
#include "defs.hpp"

class GameStack;

struct GameContext {
	GameContext(sf::RenderWindow & window);
	sf::RenderWindow * window;
};

class GameState {
public:
	typedef std::unique_ptr<GameState> Ptr;

	virtual bool draw() const = 0;
	virtual bool update(const sf::Time & deltaTime) = 0;
	virtual bool handle(const sf::Event & event) = 0;

	GameState(GameStack & stack, GameContext & context);
	virtual ~GameState() = default;
protected:
	void requestStackPush(const States::ID & state);
	void requestStackPop();
	void requestStackClear();
	GameContext mContext;

private:
	GameStack * mStack;
};

#include "GameStack.hpp"

#endif /* GAMESTATE_HPP_ */
