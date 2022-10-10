#include <stdio.h>
#include <stdlib.h>

#include "displ.h"
#include "log.h"

#include "river-layout-v3-client-protocol.h"
#include "inc1.h"
#include "inc2.h"

int main(int argc, char **argv) {
	log_info("river-xmonadwm starting");

	printf("river-xmonadwm %d %d\n", add(1, 2), add_and_double(1, 2));

	if (!displ_connect()) {
		exit(EXIT_FAILURE);
	}

	log_info("river-xmonadwm started");

	return 0;
}
