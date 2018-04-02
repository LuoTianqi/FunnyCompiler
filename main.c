#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "operate.h"


void creatTree(Statm** head,Statm** tail,int flag);
void operateTree(Statm *root);
void freeTree(Statm* root);

int line  = 1;
FILE *fp;
Variable* VARhead = NULL;
int last = 0;
char ch;

int main()
{
    Statm* head = NULL;
    Statm* tail = NULL;
    int flag = 0;

    if((fp = fopen("input.txt", "r")) == NULL){
        printf("can't open file");
    }
    else{
        ch = fgetc(fp);
        creatTree(&head,&tail,flag);
    }
    fclose(fp);

 //   printf("(%p)(%p)\n", root,root->next);

    operateTree(head);
    freeTree(head);
    FreeVar(VARhead);
    return 0;
}
