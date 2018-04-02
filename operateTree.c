#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "operate.h"
#include "calc.h"

extern int last;
extern Variable* VARhead;

void printRow(int row)
{
    if (row != last)
    {
        printf("%d ",row);
        last = row;
    }
}

int operateTree(Statm *root)
{
    printf("operate start.\n");

    Statm *pStatm;
    void* content;
    Value * valueTop;
    char*judge;
    int tag = 0;

    char* temp ;
    int temp_c = 0;

    for(pStatm = root; pStatm != NULL; pStatm = pStatm->next)
    {

        switch(pStatm->type){
            case T_int:
                printRow(pStatm->row);
                content = (Statm_int*)(pStatm->content);
                valueTop = NewVar(((Statm_int*)content)->name);

                printf("(%s)=(%s)\n",((Statm_int*)content)->name,((Statm_int*)content)->assignment);

                valueTop->elem = calculate("12"/*((Statm_int*)content)->assignment*/);   //变量操作，记得加回来*/

                break;

            case T_assign:
                printRow(pStatm->row);
                content = (Statm_int*)(pStatm->content);
                valueTop = NewVar(((Statm_int*)content)->name);

                /*     temp = ((Statm_int*)content)->assignment;
                printf("%s",temp);//谜一样的printf,不能删除
                valueTop->elem = calculate((char*)temp);   //变量操作，记得加回来*/
                break;


            case T_if:
                printRow(pStatm->row);
                content = (Statm_branch*)(pStatm->content);
                int temp;
                char* temps = "";
                int counter = 0;
                int i=0,j=0;
                judge = ((Statm_branch*)content)->judge;
                for(i=0;judge[i]!='\0';i++){
                    if(judge[i] == ','){
                        strcpy(temps,judge+j);
                        temps[i-j]='\0';
                        temp = calculate(temps);
                        j = i+1;
                    }
                }

                if(temp)
                    tag = operateTree(((Statm_branch*)content)->bodyL);
                else
                    tag = operateTree(((Statm_branch*)content)->bodyR);
                return tag;
                break;
/*
            case T_for:
                printRow(pStatm->row);
                content = (Statm_branch*)(pStatm->content);
                while(tag = operateTree(((Statm_branch*)content)->bodyL), calculate(((Statm_branch*)content)->judge) && tag==0){
                    tag = operateTree(((Statm_branch*)content)->bodyR);
                    printRow(pStatm->row);
                }
                break;

            case T_while:
                printRow(pStatm->row);
                content = (Statm_branch*)(pStatm->content);


                while(tag = operateTree(((Statm_branch*)content)->bodyL), calculate(((Statm_branch*)content)->judge) && tag==0){
                    tag = operateTree(((Statm_branch*)content)->bodyR);
                    printRow(pStatm->row);
                }
                break;

            case T_dowhile:
                content = (Statm_branch*)(pStatm->content);
                while(tag = operateTree(((Statm_branch*)content)->bodyL), calculate(((Statm_branch*)content)->judge) && tag==0){
                    tag = operateTree(((Statm_branch*)content)->bodyR);
                    printRow(pStatm->row);
                }
                break;

            case T_break:
                printRow(pStatm->row);
                return 1;
                break;
*/
            case T_printf:
                printRow(pStatm->row);
                break;

            case T_empty:
                printRow(pStatm->row);
                break;
        }

    }

    return 0;
}
