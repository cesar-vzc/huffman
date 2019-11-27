#include "../inc/huffman.h"

void
make_parent(struct node **tree, struct data *rec)
{
    int j, k;
    struct node *new = malloc(sizeof(struct node));
    struct node *tmp = NULL;
    struct node *tmp2 = NULL;

    new->data = malloc(sizeof(struct data));
    new->data->letter = ' ';
    new->data->occ = tree[0]->data->occ + tree[1]->data->occ;
    new->left = tree[0];
    new->right = tree[1];

    j = 0;
    k = 2;
    while (k < rec->size) {
	tree[j] = tree[k];
	j++;
	k++;
    }

    j = 0;
    k = 2;
    while (new->data->occ > tree[j]->data->occ) {
	if (j == rec->size - k)
	    break;
	j++;
    }
    
    tmp = tree[j];
    tree[j] = new;

    if (j == rec->size) {
	tree[j] = new;
    }	    

    while (j + 1 < rec->size) {
	tmp2 = tree[j + 1];
	tree[j + 1] = tmp;
	tmp = tmp2;
	j++;
    }

    rec->size--;
}

struct node **
tree_init(struct data *rec, int *tab, char *str)
{
    int i;
    struct node **tree = NULL;
    
    tree = malloc(sizeof(struct node *) * rec->size);
    i = 0;
    
    while (i < rec->size) {
	tree[i] = malloc(sizeof(struct node));
	tree[i]->data = malloc(sizeof(struct data));
	tree[i]->data->occ = tab[i];
	tree[i]->data->letter = str[i];
	tree[i]->left = NULL;
	tree[i]->right = NULL;
	i++;
    }
    return (tree);
}

void
destroy_tree(struct node *tree)
{
    if (tree != NULL) {
	destroy_tree(tree->left);
	destroy_tree(tree->right);
	free(tree->data);
	free(tree);
    }
}

void
print_tree(struct node *tree)
{
    if (tree == NULL) {
	puts("NULL");
	return;
    }

    if (tree->left != NULL)
	print_tree(tree->left);

    printf("%d : %c\n", tree->data->occ, tree->data->letter);

    if (tree->right != NULL)
	print_tree(tree->right);    
}
