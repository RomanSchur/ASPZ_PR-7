#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define CACHE_SIZE 5     
#define MAX_KEY_LEN 32   
#define MAX_VALUE_LEN 128 

struct Cache_struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
    time_t storage_time; 
};

struct Cache_struct cache[CACHE_SIZE];
int cache_count = 0;

int find(const char *key) {
    for (int i = 0; i < cache_count; i++) {
        if (strcmp(cache[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}

char *get(const char *key) {
    int index = find(key);

    if (index == -1) {
        return NULL;
    }

    if (time(NULL) > cache[index].storage_time) {
        cache[index].key[0] = '\0';
        cache[index].value[0] = '\0';
        return NULL;
    }
  
    if(index < cache_count - 1) {
        struct Cache_struct temp = cache[index];
        for(int i = index; i < cache_count - 1; i++) {
            cache[i] = cache[i+1];
        }
        cache[cache_count - 1] = temp;
    }
    return cache[index].value;
}

void put(const char *key, const char *value, int ttl) {
    int index = find(key);

    if (index != -1) {
        strcpy(cache[index].value, value); 
        cache[index].storage_time = time(NULL) + ttl;
        return;
    }
  
    if (cache_count == CACHE_SIZE) {
        cache[0].key[0] = '\0';
        cache[0].value[0] = '\0';
       
        for (int i = 1; i < CACHE_SIZE; i++) {
            cache[i - 1] = cache[i];
        }
        cache_count--;
    }   
    int insert_index = cache_count;
    strcpy(cache[insert_index].key, key);   
    strcpy(cache[insert_index].value, value); 
    cache[insert_index].storage_time = time(NULL) + ttl;
    cache_count++;
}

void print_cache() {   
    for (int i = 0; i < cache_count; i++) {
        if (cache[i].key[0] != '\0') {
            printf("Індекс: %d, Ключ: %s, Значення: %s\n",i, cache[i].key, cache[i].value);
        } else {
            printf("Index: %d, Порожній\n", i);
        }
    }
    printf("\n");
}

int main() {
    put("ключ1", "11", 5);
    put("ключ2", "12", 10);
    put("ключ3", "13", 3);

    print_cache();

    printf("Значення для ключа 'ключ1': %s\n", get("ключ1"));
    printf("Значення для ключа 'ключ2': %s\n", get("ключ2"));

    print_cache();

    sleep(6); 

    printf("Значення для ключа першого ключа після TTL: %s\n", get("ключ1"));

    put("ключ4", "14", 7); 

    print_cache();

    put("ключ5", "15", 2);
    put("ключ6", "16", 8);

    print_cache();
    return 0;
}