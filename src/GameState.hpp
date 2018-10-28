#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "defs.hpp"
#include "ResourceManager.hpp"
#include "Settings.hpp"

class GameStack;

struct GameContext {
	explicit GameContext(Settings & setting, sf::RenderWindow & window, ResourceManager<sf::Font, sf::String> & font,
			ResourceManager<sf::Texture, sf::String> & texture, ResourceManager<sf::SoundBuffer, sf::String> & sound);
	sf::RenderWindow * window;
	Settings & settings;
	ResourceManager<sf::Font, sf::String> & fonts;
	ResourceManager<sf::Texture, sf::String> & textures;
	ResourceManager<sf::SoundBuffer, sf::String> & sounds;
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
