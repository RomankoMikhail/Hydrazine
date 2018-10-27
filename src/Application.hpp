#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>
#include "GameStack.hpp"
#include "Settings.hpp"

class Application {
	Settings mSettings;

	const unsigned defaultScreenWidth = 1280;
	const unsigned defaultScreenHeight = 720;
	const unsigned defaultScreenAntialiasing = 0;
	const bool defaultScreenFullscreen = false;
	const bool defaultScreenVsync = false;

	sf::RenderWindow mWindow;
	GameStack mStack;


	void parseFlags(int argc, char ** argv);
	bool loadSettings(const std::string & filename);
	bool saveSettings(const std::string & filename) const;
	void defaultSettings();

public:

	void run(int argc, char ** argv);

	Application();
	virtual ~Application();
};

#endif /* APPLICATION_HPP_ */
