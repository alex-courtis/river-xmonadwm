#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "config.h"

#include "log.h"

char threshold_char[] = {
	'?',
	'D',
	'I',
	'W',
	'E',
};

char *threshold_label[] = {
	"",
	"",
	"",
	"WARNING: ",
	"ERROR: ",
};

void print_prefix(enum LogThreshold threshold, FILE *__restrict __stream) {
	static char buf[16];
	static time_t t;

	t = time(NULL);

	strftime(buf, sizeof(buf), "%H:%M:%S", localtime(&t));

	fprintf(__stream, "%c [%s] %s", threshold_char[threshold], buf, threshold_label[threshold]);
}

void log_(enum LogThreshold threshold, int eno, const char *__restrict __format, va_list __args) {
	if (threshold < config()->log_threshold) {
		return;
	}

	static FILE *stream;

	stream = threshold == ERROR ? stderr : stdout;

	print_prefix(threshold, stream);

	vfprintf(stream, __format, __args);

	if (eno) {
		fprintf(stream, " %d: %s", eno, strerror(eno));
	}

	fprintf(stream, "\n");
}

void log_debug(const char *__restrict __format, ...) {
	va_list args;
	va_start(args, __format);
	log_(DEBUG, 0, __format, args);
	va_end(args);
}

void log_info(const char *__restrict __format, ...) {
	va_list args;
	va_start(args, __format);
	log_(INFO, 0, __format, args);
	va_end(args);
}

void log_warn(const char *__restrict __format, ...) {
	va_list args;
	va_start(args, __format);
	log_(WARNING, 0, __format, args);
	va_end(args);
}

void log_warn_errno(const char *__restrict __format, ...) {
	va_list args;
	va_start(args, __format);
	log_(WARNING, errno, __format, args);
	va_end(args);
}

void log_error(const char *__restrict __format, ...) {
	va_list args;
	va_start(args, __format);
	log_(ERROR, 0, __format, args);
	va_end(args);
}

void log_error_errno(const char *__restrict __format, ...) {
	va_list args;
	va_start(args, __format);
	log_(ERROR, errno, __format, args);
	va_end(args);
}

