#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameStack.hpp"
#include "Settings.hpp"
#include "SettingsState.hpp"

class Application {
	Settings mSettings;

	sf::RenderWindow mWindow;
	GameStack mStack;

	ResourceManager<sf::Font, sf::String> fonts;
	ResourceManager<sf::Texture, sf::String> textures;
	ResourceManager<sf::SoundBuffer, sf::String> sounds;

	void parseFlags(int argc, char ** argv);

public:
	void run(int argc, char ** argv);

	Application();
	virtual ~Application();
};

#endif /* APPLICATION_HPP_ */
