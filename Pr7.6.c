#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int compare_dir_entries(const void *a, const void *b) {
    return strcmp((const char*)a, (const char*)b);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char directories[10][256];
    int dir_count = 0;           

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0) {
            continue;
        }
        
         if (strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (stat(entry->d_name, &file_stat) == -1) {
            continue;
        }

        if (S_ISDIR(file_stat.st_mode)) {            
            if (dir_count < 10) {
                strcpy(directories[dir_count], entry->d_name);
                dir_count++;
            } else {
                printf("Занадто багато підкаталогів.\n");
                break; 
            }
        }
    }
    closedir(dir);
    
    qsort(directories, dir_count, sizeof(directories[0]), compare_dir_entries);
    
    printf("Підкаталоги в алфавітному порядку:\n");
    for (int i = 0; i < dir_count; i++) {
        printf("%s\n", directories[i]);
    }

    return 0;
}