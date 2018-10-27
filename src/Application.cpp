#include "Application.hpp"

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>

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
			defaultSettings();
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

bool Application::loadSettings(const std::string & filename) {
	pugi::xml_document settingsXML;

	if (settingsXML.load_file(filename.c_str()) == false) {
		return false;
	}

	for (pugi::xml_node & root : settingsXML) {
		if (root.name() == std::string("settings")) {
			for (pugi::xml_node & settings : root) {
				if (settings.name() == std::string("screen")) {
					mSettings.screen.width = settings.attribute("width").as_uint(defaultScreenWidth);
					mSettings.screen.height = settings.attribute("height").as_uint(defaultScreenHeight);
					mSettings.screen.antialiasing = settings.attribute("antialiasing").as_uint(
							defaultScreenAntialiasing);
					mSettings.screen.fullscreen = settings.attribute("fullscreen").as_bool(defaultScreenFullscreen);
					mSettings.screen.vsync = settings.attribute("vsync").as_bool(defaultScreenVsync);
				}
			}
		}
	}
	return true;
}

bool Application::saveSettings(const std::string & filename) const {
	pugi::xml_document settingsXML;
	pugi::xml_node settingsNode = settingsXML.append_child("settings");
	pugi::xml_node screenNode = settingsNode.append_child("screen");

	screenNode.append_attribute("width") = mSettings.screen.width;
	screenNode.append_attribute("height") = mSettings.screen.height;
	screenNode.append_attribute("antialiasing") = mSettings.screen.antialiasing;
	screenNode.append_attribute("fullscreen") = mSettings.screen.fullscreen;
	screenNode.append_attribute("vsync") = mSettings.screen.vsync;

	return settingsXML.save_file(filename.c_str());
}

void Application::defaultSettings() {
	mSettings.screen.width = defaultScreenWidth;
	mSettings.screen.height = defaultScreenHeight;
	mSettings.screen.antialiasing = defaultScreenAntialiasing;
	mSettings.screen.fullscreen = defaultScreenFullscreen;
	mSettings.screen.vsync = defaultScreenVsync;
}

void Application::run(int argc, char ** argv) {
	sf::Clock deltaClock;

	parseFlags(argc, argv);
	loadSettings("settings.xml");

	sf::ContextSettings windowContext;
	windowContext.antialiasingLevel = mSettings.screen.antialiasing;

	if (mSettings.screen.fullscreen)
		mWindow.create(sf::VideoMode(mSettings.screen.width, mSettings.screen.height), "Hydrazine",
				sf::Style::Fullscreen, windowContext);
	else
		mWindow.create(sf::VideoMode(mSettings.screen.width, mSettings.screen.height), "Hydrazine", sf::Style::Default,
				windowContext);

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

	saveSettings("settings.xml");
	return;
}

Application::Application() :
		mStack(mWindow) {
	defaultSettings();

}

Application::~Application() {
	// TODO Auto-generated destructor stub
}

