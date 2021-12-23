#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readLine() 
{
  size_t size = 8;
  char* str = malloc(sizeof(char) * size);
  int c;
  size_t len;
  do {
    c = getchar();
    str[len++] = c;
    if (len == size)
      str = realloc(str, sizeof(char) * (size *= 2));
  } while (c != EOF && c != '\n' && c != '\r');
  return realloc(str, sizeof(char) * len);
}

int* splitString(const char* str, char* delim) {
  int nums[2] = {1, 2};
  return nums;
}

int main() 
{
  printf("calc:\n");
  while (1) {
    const char* rawStatement = readLine();
    int rawStatementLen = strlen(rawStatement);
    int quitCmp = strcmp(rawStatement, "x");
    int quitCmp2 = strcmp(rawStatement, "q");
    if (quitCmp == 0 && quitCmp2 == 0) {
      break;
    }
    for (int i = 0; i < rawStatementLen; i++) {
      if (rawStatement[i] == '+') {
	int nums[2];
	nums = splitString(rawStatement, "+");
      }
      else if (rawStatement[i] == '-') {
	printf("subtracting some stuff\n\n");
      }
      else if (rawStatement[i] == '*') {
	printf("multiplying some stuff\n\n");
      }
      else if (rawStatement[i] == '/') {
	printf("dividing some stuff\n\n");
      }
      else {
	continue;
      }
    }
  }
}
