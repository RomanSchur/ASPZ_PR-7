#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_info;
    char choice[1];

    dir = opendir(".");
    if (dir == NULL) {
         return 1;
   }
    while ((entry = readdir(dir))) {
        if (strstr(entry->d_name, ".c")) {
            printf("Надати дозвіл на читання для файлу %s (y/n)? ", entry->d_name);
            scanf("%s", choice); 
            
            if (choice[0] == 'y') {
                chmod(entry->d_name, 0644);
                printf("Дозвіл наданий!\n "); 
            }
        }
    }
    closedir(dir);
    return 0;
}