#include <stdio.h>
#include <stdlib.h>
#define LIMIT 20  

int main(int argc, char *argv[]) {
    FILE *file;
    char line[1024];
    int num_line = 0;

    if (argc < 2) {
        printf("Недостатня кількість аргументів\n");
        return 1;
    }

    int i;
    for (i = 1; i < argc; i++) {
        file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("Помилка відкриття файлу\n");
            return 1;
        }

        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
            num_line++;

            if (line_count % LIMIT == 0) { 
                printf("Натисніть Enter для продовження, q для виходу\n");
                int c = getchar();
                if (c == 'q') {
                    return 0;
                }               
                while (getchar() != '\n' && getchar() != EOF);
            }
        }
        fclose(file);
       num_line = 0;
    }
    return 0;
}