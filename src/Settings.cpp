#include "Settings.hpp"
#include <pugixml.hpp>

bool Settings::loadSettings(const std::string & filename) {
	pugi::xml_document settingsXML;

	if (settingsXML.load_file(filename.c_str()) == false) {
		return false;
	}

	for (pugi::xml_node & root : settingsXML) {
		if (root.name() == std::string("settings")) {
			for (pugi::xml_node & settings : root) {
				if (settings.name() == std::string("screen")) {
					screen.width = settings.attribute("width").as_uint(defaultScreenWidth);
					screen.height = settings.attribute("height").as_uint(defaultScreenHeight);
					screen.antialiasing = settings.attribute("antialiasing").as_uint(defaultScreenAntialiasing);
					screen.fullscreen = settings.attribute("fullscreen").as_bool(defaultScreenFullscreen);
					screen.vsync = settings.attribute("vsync").as_bool(defaultScreenVsync);
				}
				if (settings.name() == std::string("audio")) {
					audio.musicVolume = settings.attribute("music").as_float(defaultMusicVolume);
					audio.sfxVolume = settings.attribute("sfx").as_float(defaultSFXVolume);
				}
			}
		}
	}
	return true;
}

bool Settings::saveSettings(const std::string & filename) const {
	pugi::xml_document settingsXML;
	pugi::xml_node settingsNode = settingsXML.append_child("settings");
	pugi::xml_node screenNode = settingsNode.append_child("screen");
	pugi::xml_node audioNode = settingsNode.append_child("audio");

	screenNode.append_attribute("width") = screen.width;
	screenNode.append_attribute("height") = screen.height;
	screenNode.append_attribute("antialiasing") = screen.antialiasing;
	screenNode.append_attribute("fullscreen") = screen.fullscreen;
	screenNode.append_attribute("vsync") = screen.vsync;

	audioNode.append_attribute("sfx") = audio.sfxVolume;
	audioNode.append_attribute("music") = audio.musicVolume;

	return settingsXML.save_file(filename.c_str());
}

void Settings::defaultSettings() {
	screen.width = defaultScreenWidth;
	screen.height = defaultScreenHeight;
	screen.antialiasing = defaultScreenAntialiasing;
	screen.fullscreen = defaultScreenFullscreen;
	screen.vsync = defaultScreenVsync;

	audio.musicVolume = defaultMusicVolume;
	audio.sfxVolume = defaultSFXVolume;
}
