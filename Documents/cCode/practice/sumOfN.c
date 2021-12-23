#include <stdio.h>
#include <stdlib.h>

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
  char* input;
  int finalNum = 0;
  char finalNum_str[20];
  int input_int;

  printf("Pick a number:\n");
  input = readline();

  int n = atoi(input);

  for(int i = 0; i <=n; i++) {
    finalNum = finalNum + i;
  }

  sprintf(finalNum_str, "%d", finalNum);

  printf("%s\n", finalNum_str);
}
