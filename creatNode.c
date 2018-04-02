#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "IDfuncton.h"

extern int line;
extern FILE* fp;
extern char ch;

Statm* creatVoid()
{
    Statm* p= malloc(sizeof(Statm));

  //  printf("new:%p\n", p);
    p->row = line;
    p->type = -1;
    p->content = NULL;
    p->next = NULL;
    return p;
}


Statm* creatInt(char* name, char* assignment)
{
    Statm* p;
    p = creatVoid();
    Statm_int* content = malloc(sizeof(Statm_int));
    int i = 0;
    while(name[i]!= '\0')
    {
        (content->name)[i] = name[i];
        i++;
    }
    (content->name)[i] = name[i];
    i = 0;
    while(assignment[i]!= '\0')
    {
        (content->assignment)[i] = assignment[i];
        i++;
    }
    (content->assignment)[i] = assignment[i];

    p->content = content;
    return p;
}

Statm* creatBranch(char* judge,char*followStatm)
{
    Statm* p;
    p = creatVoid();
    Statm_branch* content = malloc(sizeof(Statm_branch));

    int i = 0;
    while(judge[i]!= '\0')
    {
        (content->judge)[i] = judge[i];
        i++;
    }
    (content->judge)[i] = judge[i];
    i = 0;
    while(followStatm[i]!= '\0')
    {
        (content->followStatm)[i] = followStatm[i];
        i++;
    }
    (content->followStatm)[i] = followStatm[i];

    p->content = content;
    return p;
}

Statm* addInt()
{
    Statm* current = NULL;
    char name[30];
    char assignment[50];
    int counter = 0;
    int x;
    char* temp;
    Statm_int* content;//用于测试，删除

    name[0] = '\0';
    assignment[0] = '\0';
    while( ch != ';'){
        if(ch == ','){
            assignment[counter] = '\0';
            current = creatInt(name,assignment);
            current = current->next;

            name[0] = '\0';
            assignment[0] = '\0';
            counter = 0;
            ch = fgetc(fp);
        }
        else{
            while(ch == ' '|| ch== '\t') ch = fgetc(fp);
            temp = getID(ch);
            x = 0;
            while(temp[x] != '\0')
            {
                name[x] = temp[x];
                x++;
            }
            name[x] = temp[x];

            while(ch == ' ' || ch == '=') ch = fgetc(fp);

            while(ch != ',' && ch != ';'){
                if(ch == ' ') ch = fgetc(fp);
                else{
                    assignment[counter] = ch;
                    counter++;
                    ch = fgetc(fp);
                }//end else
            }//end while
        }
    }
    assignment[counter] = '\0';
//printf("(%s)\n", assignment);
    current = creatInt(name,assignment);
    return current;
}
/*
Statm* addIf()
{
    Statm* current;

    while(ch == ' ') ch = fgetc(fp);
    if(ch == '(')
    {
        int tag = -1;

        char* name = NULL;
        char* assignment = NULL;
        int counter = 0;
        while(1)
        {
            ch = fgetc(fp);
            if(ch == ' ') continue;
            if(ch == '(') {tag--; continue;}

            if (ch == ')'){
                tag++;
                if (tag == 0) break;
            }

            assignment[counter] = ch;
            counter ++;
        }
        current = creatBranch(assignment);
    }
    while(ch == ' ' || ch == '\n') ch = fgetc(fp);
    Statm_branch* content;
    content = (Statm_branch*)(current->content);
    if(ch == '{')
    {
        creatTree(&(content->bodyL));
    }else
    {
        creatLeaf(&(content->bodyR);
    }
    while(ch == ' ' || ch == '\n') ch = fgetc(fp);

}

void creatLeaf(Statm** root)
{
    Statm* current;

    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_'){
                    char* word = getID();
                    int id = matchID(word);

                    switch(id)
                    {
                    case T_int:
                        current = addInt(ch);
                        break;

                    case T_assign:
                        current = addInt(ch);
                        break;

                    case T_if:
                        break;

                    case T_for:
                        break;

                    case T_while:
                        break;

                    case T_dowhile:
                        break;

                    case T_break:
                        break;

                    case T_void:
                        break;

                    case T_printf:
                        break;
                    }//end switch
                }//end if

    *root = current;
}


*/
