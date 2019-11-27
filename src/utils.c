#include "../inc/huffman.h"

void
print_tab(int tab[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
	printf("%d", tab[i]);
}

int
is_leaf(struct node *tree)
{
    return ! (tree->left) && ! (tree->right);
}

void
print_binary_code(struct node *tree, int *tab, int i)
{
    if (tree == NULL) {
	puts("NULL");
	return;
    }

    if (tree->left != NULL) {
	tab[i] = 0;
	print_binary_code(tree->left, tab, i + 1);
    }

    if (tree->right != NULL) {
	tab[i] = 1;
	print_binary_code(tree->right, tab, i + 1);
    }

    if (is_leaf(tree)) {
	printf("%d : %c\t-> ", tree->data->occ, tree->data->letter);
	print_tab(tab, i);
	putchar('\n');
    }
}

int
count_char(char *str, char c)
{
    int j;

    j = 0;
    for (long unsigned int i = 0; i < strlen(str); i++) {
	if (str[i] == c)
	    j++;
    }
    return (j);
}

int
clean_str(char *str, char *str2)
{
    long unsigned int i, j, k;
    int bool;

    bool = 0;

    for (i = 0; i < strlen(str); i++) {
	for (j = i + 1; str[j] != '\0'; j++) {
	    if (str[j] == str[i]) {
		bool = 1;
		for (k = j; str[k] != '\0'; k++) {
		    str[k] = str[k + 1];
		    str2[k] = str2[k + 1];
		}
	    }
	}
    }
    return (bool);
}

int *
convert(char* c)
{
    int len = strlen(c);
    int i;
    int *a = malloc((len + 1) * sizeof(int));

    for(i = 0; i < len; i++) {
	a[i] = c[i] - 48;
    }

    return (a);
}

void
order(int *tab, int taille, char *buffer)
{
    int i, j, p;
    char c;

    for (j = 0; j < taille; j++) {
	for (i = 0; i < taille; i++) {
	    do {
		p = tab[i];
		tab[i] = tab[i + 1];
		tab[i + 1] = p;

		c = buffer[i];
		buffer[i] = buffer[i + 1];
		buffer[i + 1] = c;
	    } while (tab[i] > tab[i + 1]);
	}
    }
}

void
need_help(void)
{
    printf("%s Usage: %s [OPTIONS] TEXTE TEXTE_2 ... TEXT_N\n"
	   "Options:\n"
	   "  -h	: Affiche l'aide est quitte.\n"
	   "  -v	: Affiche la version et quitte.\n"
	   "  -d	: Active le mode debug.\n",
	   progname, progname);
}

void
need_version(void)
{
    printf("%s Version 1.0\n", progname);
}
