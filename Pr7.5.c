#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
void list_files(const char *dirname) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char path[1024]; 

    dir = opendir(dirname);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ) {
            continue;
        }
         
        if (strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

        if (stat(path, &file_stat) == -1) {
            continue;
        }              
        printf("%s\n", path);

        if (S_ISDIR(file_stat.st_mode)) {            
            list_files(path);
        }
    }

    closedir(dir);
}

int main() {
    list_files("."); 
    return 0;
}