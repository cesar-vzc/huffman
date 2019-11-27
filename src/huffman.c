#include "../inc/huffman.h"

void
huffman_free(int *a, int *tab, char *buffer,
		  struct node **tree, struct data *data, struct comp *comp)
{
    free(a);
    free(tab);
    free(buffer);
    free(comp->arr);
    free(comp);
    free(data);
    free(tree);
}

void
huffman(char *argv)
{
    struct node **tree = NULL;
    struct node *ret = NULL;
    struct data *data = malloc(sizeof(struct data));
    struct comp *comp = malloc(sizeof(struct comp));

    char *buffer = strdup(argv);
    int *a = NULL;

    int k = strlen(argv);
    int *tab = malloc(sizeof(int) * k);
    char tmp[k];
    char tmp2[k];
    int i, n, m, count;
    long unsigned int max_size;

    tmp2[0] = '\0';

    for (long unsigned int i = 0; i < strlen(buffer); i++) {
	data->occ = count_char(buffer, buffer[i]);
	sprintf(tmp, "%d", data->occ);
	strcat(tmp2, tmp);
	data->letter = buffer[i];
    }

    while (clean_str(buffer, tmp2) != 0);

    i = 0;
    while (buffer[i]) {
	i++;
    }

    m = 0;
    if (strlen(argv) > 1 && i < 2)
	m = 1;

    if (strlen(argv) == 1) {
	puts("\nErreur: chaîne trop courte pour être compressé.\n");
	exit(0);
    } else if (m == 1) {
	puts("\nErreur: entrer minimum 2 caractères différents pour compresser.\n");
	exit(0);
    }

    a = convert(tmp2);
    order(a, i - 1, buffer);

    for (max_size = 0; max_size < strlen(buffer); max_size++);

    a[max_size] = 0;
    data->size = max_size;

    tree = tree_init(data, a, buffer);

    if (tree == NULL) {
	puts("Erreur: malloc.");
	exit(-1);
    }

    ret = huffman_tree(data, tree);

    count = 0;

    if (debug == 1) {
	puts("\nAffichage de l'arbre :\n");
	print_tree(ret);
	puts("\nAffichage du code binaire des lettres :\n");
	print_binary_code(ret, tab, count);
	putchar('\n');
    }

    n = 0;
    comp->b = 0x00;
    comp->arr = malloc(sizeof(int) * strlen(argv));
    comp->size = 0;
    comp->id = 0;

    printf("Texte reçu :\n\n%s\n", argv);


    puts("\n-------------------------------------\nCompression :\n");


    while (argv[n]) {
	comp = final_code(ret, tab, count, argv[n], comp);
	if (debug == 1)
	    putchar('\n');
	n++;
    }

    puts("\tCode binaire :\n");

    for (int i = 0; i <= comp->id; ++i)
	BIT_PRINT(comp->arr[i], xxxx);

    puts("\n\n\tCode compressé :\n");

    for (int i = 0; i <= comp->id; ++i)
	printf("%x", comp->arr[i]);
    printf("\n-------------------------------------");
    if (debug == 1)
	printf(" -> Dernier octet : [ %d ] bits initialisés.", comp->size);
    putchar('\n');


    puts("\nTexte décompressé :\n");
    huffdecompress(ret, comp->arr, comp->size, comp->id);

    destroy_tree(ret);
    huffman_free(a, tab, buffer, tree, data, comp);
    if (debug == 1)
	puts("\nMémoire de l'arbre libérée.\n");
}
