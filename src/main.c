#include <stdio.h>
#include <stdlib.h>

#include "displ.h"
#include "log.h"

#include "river-layout-v3-client-protocol.h"

int main(int argc, char **argv) {
	log_info("river-xmonadwm starting");

	if (!displ_connect()) {
		exit(EXIT_FAILURE);
	}

	log_info("river-xmonadwm started");

	return 0;
}
