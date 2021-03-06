#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <string>

struct ScreenSettings {
	unsigned width, height;
	unsigned antialiasing;
	bool fullscreen;
	bool vsync;
};

struct AudioSettings {
	float sfxVolume;
	float musicVolume;
};

class Settings {
	const unsigned defaultScreenWidth = 1280;
	const unsigned defaultScreenHeight = 720;
	const unsigned defaultScreenAntialiasing = 0;
	const bool defaultScreenFullscreen = false;
	const bool defaultScreenVsync = false;
	const float defaultSFXVolume = 50.0f;
	const float defaultMusicVolume = 50.0f;
public:
	ScreenSettings screen;
	AudioSettings audio;

	bool loadSettings(const std::string & filename);
	bool saveSettings(const std::string & filename) const;
	void defaultSettings();
};

#endif /* SETTINGS_HPP_ */
