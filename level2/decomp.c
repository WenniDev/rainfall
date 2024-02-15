#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void p(void) {
  int ret_addr;
  char buffer [76];
  
  fflush(stdout);
  gets(buffer);
  if ((ret_addr & 0xb0000000) == 0xb0000000) {
    printf("(%p)\n", &ret_addr);
    exit(1);
  }
  puts(buffer);
  strdup(buffer);
  return;
}

int main(void) {
  p();
  return 0;
}