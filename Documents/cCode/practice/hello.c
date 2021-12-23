#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline() {
  size_t size = 80;
  char* str = malloc(sizeof(char) * size);
  int c;
  size_t len = 0;
  while (EOF != (c = getchar()) && c != '\r' && c != '\n') {
    str[len++] = c;
    if(len == size) str = realloc(str, sizeof(char) * (size *= 2));
  }
  str[len++]='\0';
  return realloc(str, sizeof(char) * len);
}

int main() {
  printf("What is your name?\n");
  char* name = readline();
  int comparison1 = strcmp(name, "Bob");
  int comparison2 = strcmp(name, "Alice");
  if(comparison1==0)  
    printf("Name is Bob\n");  
  else if (comparison2==0) 
    printf("Name is Alice\n");  
  else
    printf("Name is not anything\n");  
  return 0;  
}

