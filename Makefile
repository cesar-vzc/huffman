GCC=			/usr/bin/gcc
EXEC=			huffman
S=			./src/


CSOURCE=        	$(S)main.c		\
			$(S)error_case.c	\
			$(S)utils.c		\
			$(S)huffman.c		\
			$(S)tree.c		\
			$(S)huffman_compress.c	\
			$(S)huffman_decompress.c

OBJS=			$(CSOURCE:.c=.o)

CFLAGS=         	-g -O2 -I $(S) -Wall -W -Werror

all:			$(OBJS) $(EXEC)

$(EXEC):
			$(GCC) -o $@ $(OBJS)

.c.o:
			$(GCC) $(CFLAGS) -o $@ -c $<

.PHONY: clean  distclean

clean:
			@rm $(S)*.o

distclean:
			@rm $(EXEC)
