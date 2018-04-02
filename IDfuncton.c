#include <stdio.h>
#include <stdlib.h>
#include "define.h"

extern FILE *fp;
extern char ch;

char *keyword[] = {"int","if","for","while","do","break","printf","","else"};

char* getID()
{
    int count = 0;
    char word[50] = "a";
    while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' || (ch >= '0' && ch<= '9')) {
        word[count++] = ch;
        ch = fgetc(fp);
    }
    word[count] = '\0';

    return word;
}

int matchID(char* word)
{
    int i;
    for (i=0; i < 9; i++) {
        if(strcmp(word, keyword[i]) == 0){
            return i;
        }
    }
    return 7;
}
