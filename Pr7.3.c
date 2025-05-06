#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
    FILE *file;
    char line[1024];
    
    if (argc != 3) {
      printf("Не передано всіх аргументів!");
      return 1;
    }

    char *file_name = argv[1];
    file = fopen(file_name, "r");

    if (file == NULL) {
      printf("Не вдалося відкрити файл!");
      return 1;
    }
   
    while (fgets(line, sizeof(line), file) != NULL) {
      if (strstr(line, argv[2]) != NULL) {
          printf("%s", line); 
      }
    }

    fclose(file);
    return 0;
}