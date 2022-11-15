#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

enum Layout {
	MONOCLE = 1,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	MID,
};

enum LogThreshold {
	DEBUG = 1,
	INFO,
	WARNING,
	ERROR,
};

struct Config {
	enum Layout layout;
	uint32_t count_master;
	double ratio_master;
	double ratio_stack;
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

