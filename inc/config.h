#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

enum Layout {
	LEFT = 1,
	RIGHT,
	TOP,
	BOTTOM,
	MONOCLE,
	MID,
};

enum Stack {
	EVEN = 1,
	DIMINISH,
	DWINDLE,
};

struct Config {
	enum Layout layout;
	enum Stack stack;
	uint32_t count_master;
	double ratio_master;
};

extern struct Config cfg;

enum LogThreshold {
	DEBUG = 1,
	INFO,
	WARNING,
	ERROR,
};

extern enum LogThreshold log_threshold;

// build cfg from user's args
void config_build(int argc, char **argv);

#endif // CONFIG_H
