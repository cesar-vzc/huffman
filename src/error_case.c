#include "../inc/huffman.h"

void
prog_parse_options(int argc, char **argv)
{
    int i;

    for (i = 0; i < argc; i++) {
	if (argv[i][0] == '-') {
	    if (!strcmp(argv[i], "-h")) {
		need_help();
		exit(0);
	    } else if (!strcmp(argv[i], "-v")) {
		need_version();
		exit(0);
	    } else if (!strcmp(argv[i], "-d"))
		debug = 1;
	}
    }
}
