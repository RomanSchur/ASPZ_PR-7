#include <stdio.h>
int main(){
  FILE *Rwho = popen("rwho","r");
   if (Rwho == NULL) {
        printf("Помилка popen rwho !\n");
        return 1;
   }
   
  FILE *More = popen ("more" , "w");
  if (More == NULL) {
        printf("Помилка popen more !\n");
        pclose(Rwho);
        return 1;
   }

  char res_rwho[256];
  while (fgets(res_rwho , sizeof(res_rwho), Rwho)){
     fputs(res_rwho , More);
  }

  pclose(Rwho);
  pclose(More);
  return 0;
}