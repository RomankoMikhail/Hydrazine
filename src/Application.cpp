#include "Application.hpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Button.hpp"
#include "pugixml.hpp"

void printHelp() {
	std::cout << "Hydrazine - arguments and help options" << std::endl;
	std::cout << std::setw(8) << std::left << " -r" << "Reset all settings to default" << std::endl;
	std::cout << std::setw(8) << std::left << " -h" << "Display this help" << std::endl;
}

void Application::parseFlags(int argc, char ** argv) {
	int opt = getopt(argc, argv, "rh");
	while (opt != -1) {
		switch (opt) {
		case 'r':
			mSettings.defaultSettings();
			break;
		case 'h':
			printHelp();
			exit(0);
			break;
		default:
			break;
		}
		opt = getopt(argc, argv, "rh");
	}
}


void testFunc(void) {
	std::cout << "Hello world!" << std::endl;
}

void Application::run(int argc, char ** argv) {
	sf::Clock deltaClock;
	parseFlags(argc, argv);
	mSettings.loadSettings("settings.xml");

	sf::ContextSettings windowContext;
	windowContext.antialiasingLevel = mSettings.screen.antialiasing;

	if (mSettings.screen.fullscreen)
		mWindow.create(sf::VideoMode(mSettings.screen.width, mSettings.screen.height), "Hydrazine",
				sf::Style::Fullscreen, windowContext);
	else
		mWindow.create(sf::VideoMode(mSettings.screen.width, mSettings.screen.height), "Hydrazine", sf::Style::Default,
				windowContext);

	mStack.registerState<SettingsState>(States::Settings);
	mStack.pushState(States::Settings);

	while (mWindow.isOpen()) {
		sf::Time deltaTime = deltaClock.restart();
		sf::Event event;

		mStack.update(deltaTime);

		while (mWindow.pollEvent(event)) {
			mStack.handle(event);
			if (event.type == sf::Event::Closed) {
				mWindow.close();
			}
		}

		mWindow.clear();
		mStack.draw();
		mWindow.display();
	}

	mSettings.saveSettings("settings.xml");
	return;
}

Application::Application() :
		mStack(GameContext(mSettings, mWindow, fonts, textures, sounds)) {
	mSettings.defaultSettings();
	fonts.create("default").loadFromFile("fonts/LiberationMono-Bold.ttf");
	sounds.create("button_click").loadFromFile("sound/button_click.wav");
	sounds.create("button_over").loadFromFile("sound/button_rollover.wav");
}

Application::~Application() {
	// TODO Auto-generated destructor stub
}

