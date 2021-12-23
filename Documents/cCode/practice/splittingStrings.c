#include <stdio.h>
#include <string.h>

int main()
{
    char str[] = "Geeks-for-Geeks";
 
    // Returns first token
    char *token = strtok(str, "-");
    char *token2 = strtok(NULL, "-");
    char *token3 = strtok(NULL, "-");
    char *token4 = strtok(NULL, "-");

    // Keep printing tokens while one of the
    // delimiters present in str[].
    /* while (token != NULL) */
    /* { */
    /*     printf("%s\n", token); */
    /*     token = strtok(NULL, "-"); */
    /* } */

        printf("%s\n", token);
        printf("%s\n", token2);
        printf("%s\n", token3);
 
    return 0;
}
