#include "../inc/huffman.h"

struct node *
huffman_tree(struct data *rec, struct node **tree)
{
    while (rec->size > 1) {
	make_parent(tree, rec);
    }
    return (tree[0]);
}

struct comp *
compress(int tab[], int n, struct comp *comp)
{
    int i, j;

    j = 0;
    while (j < n || comp->size < 8) {

	if (comp->size == 8) {
	    comp->arr[comp->id] = comp->b;
	    comp->b = 0;
	    comp->size = 0;
	    comp->id++;
	    if (debug == 1)
		printf("Octet n°%d\n", comp->id);
	}

	if (j < n)
	    comp->b = comp->b << 1;
	else {
	    comp->arr[comp->id] = comp->b;
	    break;
	}
	if (tab[j] == 0)
	    comp->b |= 0x00;
	else
	    comp->b |= 0x01;
	j++;
	comp->size++;
    }
    comp->arr[comp->id] = comp->b;

    if (debug == 1) {
	BIT_PRINT(comp->b, xxxx);
	printf(" <- ");

	for (i = 0; i < n; ++i)
	    printf("%d", tab[i]);
    }
    if (debug == 1)
	putchar('\n');

    return (comp);
}

struct comp *
final_code(struct node *tree, int *tab, int i, char c, struct comp *comp)
{
    if (tree == NULL) {
	puts("NULL");
	return (comp);
    }

    if (tree->left != NULL) {
	tab[i] = 0;
	comp = final_code(tree->left, tab, i + 1, c, comp);
    }

    if (tree->right != NULL) {
	tab[i] = 1;
	comp = final_code(tree->right, tab, i + 1, c, comp);
    }

    if (is_leaf(tree) && tree->data->letter == c) {
	comp = compress(tab, i, comp);
	return (comp);
    }
    return (comp);
}
