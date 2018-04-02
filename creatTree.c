#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "creatNode.h"
#include "IDfuncton.h"

extern int line;
extern FILE *fp;

int depth = 0;
extern char ch;

int y=0;//测试用，删掉


void creatTree(Statm** head,Statm** tail,int flag)
{
 //   layer++;
  //  printf("layer = %d\n",layer);
  printf("\t in.\n");

    Statm* current = NULL;

    int back;//用于回溯
    char judgement[50] = {""};
    char followStatm[50] = {""};
    int counter = 0;
    Statm_int* content;//用于测试，删除
    int x = 0;
    Statm* tail_L = NULL;

    int time = 0;

    while( ch!= EOF){

        switch(flag)
        {
        case 0:
            if(ch == '}') {
            //        printf("(%c)",ch);
                ch = fgetc(fp);
                    printf("\t out.\n",ch);
                return ;
            }
            break;
        case 1:
            if(time == 1) {
           //     printf("(%c)",ch);
               printf("\t out.\n",ch);
                return ;
            }
        }
/*
if((*head) != NULL){
content = ((Statm_int*)((*head)->content));//²âÊÔÓÃ£¬É¾µô
printf("(1)%d,%s=%s,",(*head)->type,content->name, content->assignment);//²âÊÔÓÃ£¬É¾µô
printf("(%p,%p)\n",*head,*tail);
}//²âÊÔÓÃ£¬É¾µô
*/
        switch(ch)
        {

            case ' ':
                break;

            case '\t':
                break;

            case '\n':
                line++;
                break;

            case ';':
                current = creatVoid();
                if(*head == NULL){
                    *head = current;
                    }
                    else{
                    (*tail)->next = current;
                    }
                    *tail = current;
                current = current->next;
                time++;

                break;

            case '/':
                ch = fgetc(fp);
                if (ch == '/'){
                    while(ch != '\n') ch = fgetc(fp);
                    line++;
                }else if(ch == '*'){
                    while(1){
                        ch = fgetc(fp);
                        if(ch == '\n'){
                            line++;
                        }else if(ch == '*')
                        {
                            ch = fgetc(fp);
                            if(ch == '/')
                            {
                                ch = fgetc(fp);
                                break;
                            }
                        }
                    }//end while
                }//end if
                break;

            default:
                time++;
                if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_'){
                    Statm_int* content;
                    char* word = getID();
                    int id = matchID(word);
                    printf("%s\t\t\t\n",word,id);

                    switch(id)
                    {
                    case T_int:
                        current = addInt(ch);
                        current->type = T_int;
content = ((Statm_int*)(current)->content);//²âÊÔÓÃ£¬É¾µô
(content->assignment)[0] = '\0';

printf("%d,%s=%s\n",current->type,content->name, content->assignment);//²âÊÔÓÃ£¬É¾µô
//printf("(%p,%p)\n",*head,*tail);//}//²âÊÔÓÃ£¬É¾µô


                        break;

                    case T_assign:
                        back = 0;
                        while(word[back]!='\0') back++;
                        fseek(fp,-back-1,SEEK_CUR);

                        current = addInt(ch);
                        current->type = T_assign;
                        break;

                    case T_if:
                        judgement[0] = '\0';
                        followStatm[0] = '\0';
                        while(ch == ' ') ch = fgetc(fp);
                        counter = 0;
                        if(ch == '('){
                            x = -1;
                            ch = fgetc(fp);
                            while(x != 0)
                            {
                                if(ch == ' ');
                                else{
                                    judgement[counter] = ch;
                                    counter++;

                                    if(ch == '(') x--;
                                    else if(ch == ')') x++;
                                }
                                ch = fgetc(fp);
                            }
                        }
                        judgement[counter-1] = '\0';
        printf("%s\n", judgement);

                        current = creatBranch(judgement,followStatm);
//处理if为真
                        while(ch ==' ' || ch == '\t' || ch == '\n'){
                            if(ch == '\n') line++;
                            ch = fgetc(fp);
                        }
                        ((Statm_branch*)(current->content))->bodyL = NULL;
                        tail_L = NULL;
                        if(ch != '{')
                        {
                            creatTree(&(((Statm_branch*)(current->content))->bodyL), &tail_L,1);
                        }
                        else{
                            creatTree(&(((Statm_branch*)(current->content))->bodyL), &tail_L,0);
                        }
//处理else
                        while(ch ==' ' || ch == '\t' || ch == '\n'){
                            if(ch == '\n') line++;
                            ch = fgetc(fp);
                        }

                        if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_'){

                            if(ch == 'e'){
                            word = getID();
                            id = matchID(word);

                            if(id == T_else){
                                    printf("%s(%d)\t\t\t\n",word,id);
                                while(ch ==' ' || ch == '\t' || ch == '\n'){
                                if(ch == '\n') line++;
                                    ch = fgetc(fp);
                                }
                                ((Statm_branch*)(current->content))->bodyR = NULL;
                                tail_L = NULL;
                                if(ch != '{')
                                {
                                    creatTree(&(((Statm_branch*)(current->content))->bodyR), &tail_L,1);
                                }
                                else{
                                    creatTree(&(((Statm_branch*)(current->content))->bodyR), &tail_L,0);
                                }
                            }
                            else{
                                while(ch != 'e'){
                                fseek(fp,-2,SEEK_CUR);
                                ch = fgetc(fp);
                                }
                            }

                            }

                        }


                        break;


                    case T_for:
                        judgement[0] = '\0';
                        followStatm[0] = '\0';
                        while(ch == ' ') ch = fgetc(fp);
                        counter = 0;

                        current = NULL;
                        tail_L = NULL;
                        if(ch == '('){
                            ch = fgetc(fp);
                            creatTree(&current, &tail_L,1);

                     //       current = current->next;

                            while(ch!=';')
                            {
                                if(ch == ' '|| ch == '\t') {;}
                                else if(ch == '\n') {line++;}
                                else{
                                    judgement[counter] = ch;
                                    counter++;
                                }
                                ch = fgetc(fp);
                            }

                            judgement[counter] = '\0';
            printf("(%s)\n", judgement);

                            x = -1;
                            counter = 0;
                            ch = fgetc(fp);
                            while(x != 0)
                            {
                                if(ch == ' '|| ch == '\t') ;
                                else if(ch == '\n') {line++;}
                                else{
                                    followStatm[counter] = ch;
                                    counter++;

                                    if(ch == '(') x--;
                                    else if(ch == ')') x++;
                                }
                                ch = fgetc(fp);
                            }
                            followStatm[counter-1] = '\0';
            printf("(%s)\n", followStatm);
                        }

                        current = creatBranch(judgement,followStatm);

                        while(ch ==' ' || ch == '\t' || ch == '\n'){
                            if(ch == '\n') line++;
                            ch = fgetc(fp);
                        }

                        ((Statm_branch*)(current->content))->bodyL = NULL;
                        tail_L = NULL;
                        if(ch != '{')
                        {
                            creatTree(&(((Statm_branch*)(current->content))->bodyL), &tail_L,1);
                        }
                        else{
                            creatTree(&(((Statm_branch*)(current->content))->bodyL), &tail_L,0);
                        }


                        break;

                    case T_while:
                        judgement[0] = '\0';
                        followStatm[0] = '\0';
                        while(ch == ' ') ch = fgetc(fp);
                        counter = 0;
                        if(ch == '('){
                            x = -1;
                            ch = fgetc(fp);
                            while(x != 0)
                            {
                                if(ch == ' ');
                                else{
                                    judgement[counter] = ch;
                                    counter++;

                                    if(ch == '(') x--;
                                    else if(ch == ')') x++;
                                }
                                ch = fgetc(fp);
                            }
                        }
                        judgement[counter-1] = '\0';
        printf("%s\n", judgement);

                        current = creatBranch(judgement,followStatm);

                        while(ch ==' ' || ch == '\t' || ch == '\n'){
                            if(ch == '\n') line++;
                            ch = fgetc(fp);
                        }

                        ((Statm_branch*)(current->content))->bodyL = NULL;
                        tail_L = NULL;
                        if(ch != '{')
                        {
                            creatTree(&(((Statm_branch*)(current->content))->bodyL), &tail_L,1);
                        }
                        else{
                            creatTree(&(((Statm_branch*)(current->content))->bodyL), &tail_L,0);
                        }
                        break;

                    case T_dowhile:
                        judgement[0] = '\0';
                        followStatm[0] = '\0';
                        current = creatBranch(judgement,followStatm);

                        while(ch ==' ' || ch == '\t' || ch == '\n'){
                            if(ch == '\n') line++;
                            ch = fgetc(fp);
                        }
                        ((Statm_branch*)(current->content))->bodyL = NULL;
                        tail_L = NULL;
                        if(ch != '{')
                        {
                            creatTree(&(((Statm_branch*)(current->content))->bodyL), &tail_L,1);
                        }
                        else{
                            creatTree(&(((Statm_branch*)(current->content))->bodyL), &tail_L,0);
                        }

                        while(ch ==' ' || ch == '\t' || ch == '\n'){
                            if(ch == '\n') line++;
                            ch = fgetc(fp);
                        }

                        counter = 0;
                        while(ch != '(') ch = fgetc(fp);
                        if(ch == '('){
                            x = -1;
                            ch = fgetc(fp);
                            while(x != 0)
                            {
                                if(ch == ' ');
                                else{
                                    judgement[counter] = ch;
                                    counter++;

                                    if(ch == '(') x--;
                                    else if(ch == ')') x++;
                                }
                                ch = fgetc(fp);
                            }
                        }
                        judgement[counter-1] = '\0';
        printf("(%s)\n", judgement);

                        int i =0;
                        while(judgement[i] != '\0'){
                        (((Statm_branch*)(current->content))->judge)[i] = judgement[i];
                        i++;
                        }
                        (((Statm_branch*)(current->content))->judge)[i] = judgement[i];

                        break;

                    case T_break:
                        current = creatVoid();
                        current->type = T_break;
                        break;

                    case T_empty:
                        current = creatVoid();
                        current->type = T_empty;
                        break;


                    case T_printf:
                        current = creatVoid();
                        current->type = T_printf;
                        while(ch != '"') ch = fgetc(fp);
                        ch = fgetc(fp);
                        while(ch != '"') ch = fgetc(fp);
                        while(ch != ';') ch = fgetc(fp);
                        break;

                    }//end switch


                   if(*head == NULL){
                    *head = current;
                    }
                    else{
                    (*tail)->next = current;
                    }
                    *tail = current;
                    current=current->next;

                }//end if
/*
content = ((Statm_int*)((*head)->content));//²âÊÔÓÃ£¬É¾µô
printf("(2)%d,%s=%s,",(*head)->type,content->name, content->assignment);//²âÊÔÓÃ£¬É¾µô
printf("(%p,%p)\n",*head,*tail);//}//²âÊÔÓÃ£¬É¾µô
*/
                break;
        }//end switch

    ch = fgetc(fp);
    }//end while

}

