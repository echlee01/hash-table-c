#include "hash_table.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    ht_hash_table* ht = ht_new();
    printf("test\n");
    ht_insert(ht, "battlebit", "addiction");
    printf("1 - %s\n", ht_search(ht, "battlebit"));

    printf("dogshit game\n");
    ht_insert(ht, "battlebit", "great game");
    printf("3 - %s\n", ht_search(ht, "battlebit"));
    free_ht(ht);

    return 0;
}