// hash_table.h
//item
typedef struct {
    char* key;
    char* value;
} ht_item;

// ht
typedef struct {
    int base_size;
    int size;
    int count;
    ht_item** items;
} ht_hash_table;

ht_hash_table* ht_new();

void free_ht(ht_hash_table* ht);

int hash(const char *str,const int prime, const int num_buckets);

void ht_insert(ht_hash_table* ht,  const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h,  const char* key);