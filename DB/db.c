/* db.c - toy in-memory key/value store, following along a C tutorial */
/* TODO: hash table instead of linear array, persistence to disk, better error handling */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 128
#define KEY_LEN 64
#define VAL_LEN 256

typedef struct {
    char key[KEY_LEN];
    char value[VAL_LEN];
    int used;
} entry_t;

static entry_t table[MAX_ENTRIES];

int db_set(const char *key, const char *value) {
    for (int i = 0; i < MAX_ENTRIES; i++) {
        if (table[i].used && strcmp(table[i].key, key) == 0) {
            strncpy(table[i].value, value, VAL_LEN - 1);
            return 0;
        }
    }
    for (int i = 0; i < MAX_ENTRIES; i++) {
        if (!table[i].used) {
            strncpy(table[i].key, key, KEY_LEN - 1);
            strncpy(table[i].value, value, VAL_LEN - 1);
            table[i].used = 1;
            return 0;
        }
    }
    return -1; // table full
}

char *db_get(const char *key) {
    for (int i = 0; i < MAX_ENTRIES; i++) {
        if (table[i].used && strcmp(table[i].key, key) == 0) {
            return table[i].value;
        }
    }
    return NULL;
}

int main() {
    db_set("host", "127.0.0.1");
    db_set("port", "8080");

    char *v = db_get("host");
    if (v) {
        printf("host = %s\n", v);
    }

    // no CLI parsing yet, no delete, no persistence
    // next: read commands from stdin like SET key value / GET key

    return 0;
}
