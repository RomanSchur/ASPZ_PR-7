#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    char response[2];

    dir = opendir(".");
    if (dir == NULL) {        
        return 1;
    }   

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0) {
            continue;
        }
        if (strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        printf("Видалити '%s'? (y/n): ", entry->d_name);
        scanf("%1s", response); 

        if (response[0] == 'y') {
            if (remove(entry->d_name) == 0) {
                printf("Видалено '%s'\n", entry->d_name);
            } else {
            printf("Пропущено '%s'\n", entry->d_name);
        }
     }
   }

    closedir(dir);
    return 0;
}