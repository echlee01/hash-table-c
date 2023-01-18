#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash_table.h"
#include "prime.h"

#define PRIME1 151
#define PRIME2 167 
#define HT_INITIAL_SIZE 53

static ht_item HT_DELETED_ITEM = {NULL, NULL};

static ht_item* ht_new_item(const char* k, const char* v) {
    ht_item* i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}

static ht_hash_table* ht_new_sized(const int base_size) {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));
    assert(ht);

    ht->base_size = base_size;
    ht->size = next_prime(base_size);
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));

    return ht;
}

ht_hash_table* ht_new() {
    return ht_new_sized(HT_INITIAL_SIZE);
}

// free ht item
static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}

// free ht
void free_ht(ht_hash_table* ht) {
    for(int i = 0; i < (ht->size); i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) {
            ht_del_item(item);
        }
    }
    
    free(ht->items);
    free(ht);
}

// choose prime number bigger than 128
int hash(const char *str, const int prime, const int num_buckets) {
    int hash = 0;
    int string_len = strlen(str);
    for (int i = 0; i<string_len; i++) {
        hash += pow(prime, (string_len - (i+1))) * str[i];
        hash = hash % num_buckets;
    }

    
    return hash;
}

int double_hash(const char *str, const int collisions, const int num_buckets) {
    int hash1 = hash(str, PRIME1, num_buckets);
    int hash2 = hash(str, PRIME2, num_buckets);

    int index = (hash1 + collisions * (hash2 + 1)) % num_buckets;
    return index;
}

void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    const int load = (ht->count)*100 / ht->size;
    
    if (load > 70) {
        resize_up(ht);
    }
    
    ht_item* item = ht_new_item(key, value);
    int index = double_hash(key, 0, ht->size);
    ht_item* cur_item = ht->items[index];
    int collision = 1;

    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
        if (strcmp(cur_item->key, key) == 0) {
            ht_del_item(cur_item);
            ht->items[index] = item;
            return;
        }
        index = double_hash(key, collision, ht->size);
        cur_item = ht->items[index];
        collision++;

    }

    ht->items[index] = item;
    ht->count++;
}

char* ht_search(ht_hash_table* ht, const char* key){

    int index = double_hash(key, 0, ht->size);
    ht_item* cur_item = ht->items[index];
    int collision = 1;
    
    while (cur_item != NULL) {
        if (cur_item != &HT_DELETED_ITEM) {
            if (strcmp(cur_item->key, key) == 0) {
                return cur_item->value;
            }
        }
        
        index = double_hash(key, collision, ht->size);
        cur_item = ht->items[index];
        collision++;
    }

    return NULL;
}

void ht_delete(ht_hash_table* ht, const char* key) {
    int index = double_hash(key, 0, ht->size);
    int collision = 1;
    ht_item* cur_item = ht->items[index];
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        ht_resize_down(ht);
    }
    while (cur_item != NULL) {
        if (cur_item != &HT_DELETED_ITEM) {
            if (strcmp(cur_item->key, key) == 0) {
                ht_del_item(cur_item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = double_hash(key, collision, ht->size);
        cur_item = ht->items[index];
        collision++;
    }
    ht->count--;
}

static void ht_resize(ht_hash_table* ht, const int new_size) {
    if (new_size < HT_INITIAL_SIZE) {
        return;
    }

    ht_hash_table* new_ht = ht_new_sized(new_size);

    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];

        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_ht, item->key, item->value);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;
 
    ht_item* tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    free_ht(new_ht);
}

static void resize_up(ht_hash_table* ht) {
    int new_size = next_prime(ht->base_size * 2);
    
    return ht_resize(ht, new_size);
}

static void resize_down(ht_hash_table* ht) {
    int new_size = next_prime(ht->base_size / 2);
    return ht_resize(ht, new_size);
}


