
#include <stdio.h>
int m;

void v(void) {
  char buff [520];
  
  fgets(buff, 512, stdin);
  printf(buff);
  if (m == 64) {
    fwrite("Wait what?!\n", 1, 12, stdout);
    system("/bin/sh");
  }
  return;
}

int main(void) {
  v();
  return 0;
}