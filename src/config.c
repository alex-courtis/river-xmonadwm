// IWYU pragma: no_include <bits/getopt_core.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "log.h"

#include "config.h"

#define LAYOUT_DEFAULT LEFT

#define STACK_DEFAULT EVEN

#define COUNT_MASTER_MIN 1
#define COUNT_MASTER_DEFAULT 1

#define RATIO_MASTER_MIN 0.1
#define RATIO_MASTER_DEFAULT 0.5
#define RATIO_MASTER_MAX 0.9

struct Config cfg = { 0 };

#define LOG_THRESHOLD_DEFAULT INFO

enum LogThreshold log_threshold = LOG_THRESHOLD_DEFAULT;

static struct option long_options[] = {
	{ "layout",        required_argument, 0, 'l' },
	{ "count-master",  required_argument, 0, 'c' },
	{ "ratio-master",  required_argument, 0, 'r' },
	{ "stack",         required_argument, 0, 's' },
	{ "help",          no_argument,       0, 'h' },
	{ "log-threshold", required_argument, 0, 'L' },
	{ "version",       no_argument,       0, 'v' },
	{ 0,               0,                 0,  0  }
};
static char *short_options = "l:c:r:s:hL:v";

struct NameVal {
	unsigned int val;
	char *name;
};

static struct NameVal layouts[] = {
	{ .val = MONOCLE,	.name = "monocle",	},
	{ .val = LEFT,		.name = "left",		},
	{ .val = RIGHT,		.name = "right",	},
	{ .val = TOP,		.name = "top",		},
	{ .val = BOTTOM,	.name = "bottom",	},
	{ .val = MID,		.name = "mid",		},
	{ .val = 0,			.name = NULL,		},
};

static struct NameVal stacks[] = {
	{ .val = EVEN,		.name = "even",		},
	{ .val = DIMINISH,	.name = "diminish",	},
	{ .val = DWINDLE,	.name = "dwindle",	},
	{ .val = 0,			.name = NULL,		},
};

static struct NameVal log_thresholds[] = {
	{ .val = DEBUG,		.name = "debug",	},
	{ .val = INFO,		.name = "info",		},
	{ .val = WARNING,	.name = "warning",	},
	{ .val = ERROR,		.name = "error",	},
	{ .val = DEBUG,		.name = "debug",	},
	{ .val = 0,			.name = NULL,		},
};

const char *name(struct NameVal *name_vals, unsigned int val) {
	if (!name_vals) {
		return NULL;
	}
	for (int i = 0; name_vals[i].name; i++) {
		if (val == name_vals[i].val) {
			return name_vals[i].name;
		}
	}
	return NULL;
}

unsigned int val(struct NameVal *name_vals, const char *name) {
	if (!name_vals || !name) {
		return 0;
	}
	for (int i = 0; name_vals[i].name; i++) {
		if (strcasecmp(name_vals[i].name, name) == 0) {
			return name_vals[i].val;
		}
	}
	return 0;
}

const char *layout_name(enum Layout layout) {
	return name(layouts, layout);
}

enum Layout layout_val(const char *name) {
	return val(layouts, name);
}

const char *stack_name(enum Stack stack) {
	return name(stacks, stack);
}

enum Stack stack_val(const char *name) {
	return val(stacks, name);
}

const char *log_threshold_name(enum LogThreshold log_threshold) {
	return name(log_thresholds, log_threshold);
}

enum LogThreshold log_threshold_val(const char *name) {
	return val(log_thresholds, name);
}

void usage(FILE *stream) {
	fprintf(stream,
			"Usage: river-xmonadwm [OPTIONS...]\n"
			"\n"
			"  -l, --la[yout]        <%s|%s|%s|%s|%s|%s>  %s\n"
			"  -c, --c[ount-master]  <int>                                %d       %d <= count\n"
			"  -r, --ratio-m[aster]  <float>                              %.1g   %.1g <= ratio <= %.1g\n"
			"  -s, --stack           <%s|%s|%s>              %s\n"
			"\n"
			"  -h, --h[elp]\n"
			"  -L, --lo[g-threshold] <%s|%s|%s|%s>           %s\n"
			"  -v, --v[ersion]\n",
			layout_name(MONOCLE), layout_name(LEFT), layout_name(RIGHT), layout_name(TOP), layout_name(BOTTOM), layout_name(MID), layout_name(LAYOUT_DEFAULT),
			COUNT_MASTER_DEFAULT, COUNT_MASTER_MIN,
			RATIO_MASTER_DEFAULT, RATIO_MASTER_MIN, RATIO_MASTER_MAX,
			stack_name(EVEN), stack_name(DIMINISH), stack_name(DWINDLE), stack_name(STACK_DEFAULT),
			log_threshold_name(DEBUG), log_threshold_name(INFO), log_threshold_name(WARNING), log_threshold_name(ERROR), log_threshold_name(LOG_THRESHOLD_DEFAULT)
		   );
}

void config_build(int argc, char **argv) {
	memset(&cfg, 0, sizeof(cfg));
	cfg.layout = LAYOUT_DEFAULT;
	cfg.stack = STACK_DEFAULT;
	cfg.count_master = COUNT_MASTER_DEFAULT;
	cfg.ratio_master = RATIO_MASTER_DEFAULT;

	int c;
	long int l;
	while (1) {
		int long_index = 0;
		c = getopt_long(argc, argv, short_options, long_options, &long_index);
		if (c == -1)
			break;
		switch (c) {
			case 'l':
				cfg.layout = layout_val(optarg);
				if (!cfg.layout) {
					fprintf(stderr, "invalid --layout %s\n\n", optarg);
					usage(stderr);
					exit(EXIT_FAILURE);
				}
				break;
			case 'c':
				l = strtol(optarg, NULL, 10);
				if (l < COUNT_MASTER_MIN) {
					fprintf(stderr, "invalid --count-master %s\n\n", optarg);
					usage(stderr);
					exit(EXIT_FAILURE);
				}
				cfg.count_master = l;
				break;
			case 'r':
				cfg.ratio_master = strtod(optarg, NULL);
				if (cfg.ratio_master < RATIO_MASTER_MIN || cfg.ratio_master > RATIO_MASTER_MAX) {
					fprintf(stderr, "invalid --ratio-master %s\n\n", optarg);
					usage(stderr);
					exit(EXIT_FAILURE);
				}
				break;
			case 's':
				cfg.stack = stack_val(optarg);
				if (!cfg.stack) {
					fprintf(stderr, "invalid --stack %s\n\n", optarg);
					usage(stderr);
					exit(EXIT_FAILURE);
				}
				break;
			case 'L':
				log_threshold = log_threshold_val(optarg);
				if (!log_threshold) {
					fprintf(stderr, "invalid --log-threshold %s\n\n", optarg);
					usage(stderr);
					exit(EXIT_FAILURE);
				}
				break;
			case 'h':
				usage(stdout);
				exit(EXIT_SUCCESS);
			case 'v':
				fprintf(stdout, "river-xmonadwm version %s\n", "TODO");
				exit(EXIT_SUCCESS);
			case '?':
			default:
				fprintf(stderr, "\n");
				usage(stderr);
				exit(EXIT_FAILURE);
		}
	}

	log_debug("layout         %s", layout_name(cfg.layout));
	log_debug("count-master   %u", cfg.count_master);
	log_debug("ratio-master   %g", cfg.ratio_master);
	log_debug("stack          %s", stack_name(cfg.stack));
	log_debug("log-threshold  %s", log_threshold_name(log_threshold));
}

