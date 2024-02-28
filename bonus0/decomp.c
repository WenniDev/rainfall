#include <stdio.h>
#include <string.h>

char *p(char *dest, char *s)
{
  char buf[4104];

  puts(s);
  read(0, buf, 4096);
  *strchr(buf, '\n') = 0;
  return strncpy(dest, buf, 20);
}

char *pp(char *dest) {
  char s1[20];
  char s2[28];

  p(s1, " - ");
  p(s2, " - ");
  strcpy(dest, s1);
  dest[strlen(dest)] = " ";
  return strcat(dest, s2);
}

int main(void)

{
  char buf[54];
  
  pp(buf);
  puts(buf);
  return 0;
}