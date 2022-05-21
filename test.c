#include <stdio.h>
#include <string.h>
int main (int argc, char *argv[])
{
  char a[50] = "hello hola";
  char* test = strtok(a, " ");
  char* test2 = strtok(NULL, "");
  printf("%s\n%s\n", test, test2);
  return 0;
}
