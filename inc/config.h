#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

enum Layout {
	LEFT = 0,
	RIGHT,
	TOP,
	BOTTOM,
	MONOCLE,
	MID,
};

enum Stack {
	EVEN = 0,
	DIMINISH,
	DWINDLE,
};

enum LogThreshold {
	INFO = 0,
	DEBUG,
	WARNING,
	ERROR,
};

struct Config {
	enum Layout layout;
	enum Stack stack;
	uint32_t count_master;
	double ratio_master;
	enum LogThreshold log_threshold;
};

// crate or replace active
void config_parse(int argc, char **argv);

// return one and only active, instantiating a default if not present
struct Config *config(void);

void config_print(void);

// destroy one and only active
void config_destroy(void);

#endif // CONFIG_H

