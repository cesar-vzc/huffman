#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIT_PRINT(y, i) do{for (i = 7; i >= 0; i--)printf("%d", ((y >> i) & 1));}while (0)

struct node {
    struct data *data;
    struct node *left;
    struct node *right;
};

struct data {
    int occ;
    char letter;
    int size;
};

struct comp {
    int b;
    int *arr;
    int id;
    int size;
};

int xxxx;
int debug;
const char *progname;

void prog_parse_options(int argc, char **argv);
void need_help(void);
void need_version(void);
void print_tab(int tab[], int n);
int is_leaf(struct node *tree);
void print_binary_code(struct node *tree, int *tab, int i);
int count_char(char *str, char c);
int clean_str(char *str, char *str2);
int * convert(char* c);
void order(int *tab, int taille, char *buffer);
void make_parent(struct node **tree, struct data *rec);
struct node ** tree_init(struct data *rec, int *tab, char *str);
void destroy_tree(struct node *tree);
void print_tree(struct node *tree);
void huffman_free(int *a, int *tab, char *buffer,
		  struct node **tree, struct data *data, struct comp *comp);
void huffman(char *argv);
struct node * huffman_tree(struct data *rec, struct node **tree);
struct comp * compress(int tab[], int n, struct comp *comp);
struct comp * final_code(struct node *tree, int *tab, int i, char c, struct comp *comp);
int huffdecompress_letter(struct node *tree, int *bytes, int *i, int id, int size, int tmp);
void huffdecompress(struct node *tree, int *byte, int size, int id);
int main(int argc, char **argv);

#endif /* ! __HUFFMAN_H__ */
