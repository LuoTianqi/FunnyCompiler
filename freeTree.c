#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "operate.h"

void freeTree(Statm* root)
{
    while(root != NULL)
    {
        Statm *temp = NULL;
        int type;

        type = root->type;
        temp = root;
        root = root->next;


        if(type == T_break || type == T_printf
           || type == T_empty)
        {
            free(temp);
        }else if(type == T_int || type == T_assign){
            free(temp->content);
            free(temp);
        }else{
            freeTree(((Statm_branch*)(temp->content))->bodyL);
            freeTree(((Statm_branch*)(temp->content))->bodyR);

            free(temp->content);
            free(temp);
        }

    }

    printf("\nfree complete.\n");
}
