// hash_table.h
//item
typedef struct {
    char* key;
    char* value;
} ht_item;

// ht
typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;

ht_hash_table* ht_new();

void free_ht(ht_hash_table* ht);