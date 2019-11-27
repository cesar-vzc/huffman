#include "../inc/huffman.h"

int
huffdecompress_letter(struct node *tree, int *bytes, int *i, int id, int size, int tmp)
{
    int buf;
    unsigned char byte;
    int bit_id[] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

    do {
	byte = bytes[*i];
	while (size > 0) {
	    if (is_leaf(tree)) {
		printf("%c", tree->data->letter);
		return (size);
	    }
	    buf = size;
	    if (debug == 1)
		printf("\t\tbyte = %x -- buf = %d -- bit_id[buf] = 0x%x\n", byte, buf, bit_id[buf]);
	    if ((byte & bit_id[buf]) == 0) {
		if (tree->left == NULL) {
		    puts("Erreur: lecture de l'arbre. (G)\n");
		    exit(-1);
		}
		tree = tree->left;
	    }
	    else {
		if (tree->right == NULL) {
		    puts("Erreur; lecture de l'arbre. (D)\n");
		    exit(-1);
		}
		tree = tree->right;
	    }
	    size--;
	}
	if (debug == 1)
	    printf("\t\tbyte = %d\n",  bytes[*i]);
	(*i)++;
	if (*i < id+1) {
	    size = (*i == id) ? tmp : 8;
	    if (debug == 1)
		printf("\t\ti = %d -- id = %d -- size = %d\n", *i, id, size);
	}
    } while (*i < id+1);
    if (is_leaf(tree)) {
	printf("%c\n", tree->data->letter);
	return (size);
    }
    return -1;
}

void
huffdecompress(struct node *tree, int *byte, int size, int id)
{
    int i;
    int tmp;

    i = 0;
    tmp = size;
    if (id == 0) {
	while (size > 0)
	    size = huffdecompress_letter(tree, byte, &i, 0, size, 0);
    } else {
	while (i < id+1) {
	    size = 8;
	    while (size > 0) {
		size = huffdecompress_letter(tree, byte, &i, id, size, tmp);
	    }
	}
    }
}
