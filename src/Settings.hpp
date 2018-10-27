#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

struct ScreenSettings {
	unsigned width, height;
	unsigned antialiasing;
	bool fullscreen;
	bool vsync;
};

struct Settings {
	ScreenSettings screen;
};

#endif /* SETTINGS_HPP_ */
