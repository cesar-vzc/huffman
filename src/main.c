#include "../inc/huffman.h"

int
main(int argc, char **argv)
{
    int i;
    char *str = NULL;
    
    str = strrchr(argv[0], '/');
    progname = (str && str[1]) ? str+1 : argv[0];
    debug = 0;
    prog_parse_options(argc, argv);
    if (argc == 1) {
	puts("error: argument missing !");
	need_help();
	return (0);
    }
    putchar('\n');
    for (i = 1; i < argc; i++) {
	if (argv[i][0] != '-') {
	    huffman(argv[i]);
	    printf("\nTexte n°%d\n\n", i);
	}
    }
    return (0);
}
