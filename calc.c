#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "operate.h"
#include "calc.h"
const char* sope[K_all+1]={"","+","-","*","/","++","--","&&","||","==","!=",">","<",">=","<=","="};
const int  prior[K_all+1]={ 0, 4 , 4 , 3 , 3 , 2  , 2  , 11 , 12 , 7  , 7  , 6 , 6 , 6  , 6,   14};
char *IntToStr(int x)
{
    static char s[25];
    sprintf(s,"%d",x);
    return s;
}
double StrToInt(char *s)
{
    return atoi(s);
}
void PushinNum(Num* Numhead,int x,char *name)
{
    Num *Numtemp,*headelem;
    if (Numhead==NULL) return;
    headelem=Numhead->next;
    if (name!=NULL) {
        Value *p;
        p=FindVar(name);
        if (p==NULL) return; else x=p->elem;
    }
    Numtemp=(Num*)malloc(sizeof(Num));
    if (name!=NULL) strcpy(Numtemp->var,name);
    Numtemp->num=x;
    Numtemp->next=headelem;
    Numhead->next=Numtemp;
}
void PopupNum(Num *Numhead,int *x,Value **p)
{
    Num *Numtemp,*headelem;
    if (Numhead==NULL) return;
    if (Numhead->next==NULL) {
        (*x)=0;
        (*p)=NULL;
        return;
    }
    headelem=Numhead->next;
    Numtemp=headelem;
    Numhead->next=headelem->next;
    (*x)=Numtemp->num;
    (*p)=FindVar(Numtemp->var);
    free(Numtemp);
}
void PushinOpe(Ope* Opehead,char *s)
{
    Ope *Opetemp,*headelem;
    int i;
    if (Opehead==NULL) return;
    headelem=Opehead->next;
    Opetemp=(Ope*)malloc(sizeof(Ope));
    strcpy(Opetemp->ope,s);
    for (i=1; i<=K_all; i++)
        if (!strcmp(sope[i],s)) {
            Opetemp->kind=i; break;
        }
    Opetemp->next=headelem;
    Opehead->next=Opetemp;
}
int PopupOpe(Ope *Opehead)
{
    Ope *Opetemp,*headelem;
    int temp;
    if (Opehead==NULL) return 0;
    if (Opehead->next==NULL) return 0;
    headelem=Opehead->next;
    Opetemp=headelem;
    Opehead->next=headelem->next;
    temp=Opetemp->kind;
    free(Opetemp);
    return temp;
}
int Operate(Num *Numhead,Ope *Opehead,int temp)//根据输入进来的运算方式分别进行运算
{
    int x1,x2;
    Value *p1,*p2;
    if (temp==K_Inc) {//因为++ --会改变变量，所以单独进行特殊判断
        PopupNum(Numhead,&x1,&p1);
        if (p1!=NULL) {
            return p1->elem++;
        }
    }
    if (temp==K_Dec) {
        PopupNum(Numhead,&x1,&p1);
        if (p1!=NULL) {
            return p1->elem--;
        }
    }
    if (temp==K_Assign) {
        PopupNum(Numhead,&x2,&p2);
        PopupNum(Numhead,&x1,&p1);
        if (p1!=NULL) {
            return p1->elem=x2;
        }
    }
    PopupNum(Numhead,&x2,&p2);
    PopupNum(Numhead,&x1,&p1);
    switch (temp)
    {
    case K_Plus:
        x1=x1+x2;
        break;
    case K_Minus:
        x1=x1-x2;
        break;
    case K_Multiply:
        x1=x1*x2;
        break;
    case K_Divide:
        x1=x1/x2;
        break;
    case K_And:
        x1=x1&&x2;
        break;
    case K_Or:
        x1=x1||x2;
        break;
    case K_Equal:
        x1=x1==x2;
        break;
    case K_Unequal:
        x1=x1!=x2;
        break;
    case K_Greater:
        x1=x1>x2;
        break;
    case K_Smaller:
        x1=x1<x2;
        break;
    case K_GreaterEqual:
        x1=x1>=x2;
        break;
    case K_SmallerEqual:
        x1=x1<=x2;
        break;
    }
    return x1;
}
void calc(int l,int r,char *st,int *sum)
{
    Num *Numhead;//操作数
    Ope *Opehead;//操作符
    int i,j,bas,temp,x,y,flag,isvar,isope;
    char temps[25];
    Numhead=(Num*)malloc(sizeof(Num));//生成栈头
    Numhead->num=0;
    strcpy(Numhead->var,"");
    Numhead->next=NULL;
    Opehead=(Ope*)malloc(sizeof(Ope));//生成栈头
    Opehead->next=NULL;
    strcpy(Opehead->ope,"");
    Opehead->kind=0;
    i=l; j=r; *sum=0; st[r+1]='\0';
    do {
        switch (st[i]) {
            case ' '://空格跳过
                i++;
                break;
            case '0':case '1':case '2':case '3':case '4':case '5'://操作数入栈
            case '6':case '7':case '8':case '9':
                memset(temps,0,sizeof(temps));
                temps[0]=st[i];
                while (i<j) {
                    if (st[i+1]>='0'&&st[i+1]<='9') {
                        i++;
                        temps[strlen(temps)]=st[i];
                    } else break;
                }
                i++;
                PushinNum(Numhead,StrToInt(temps),NULL);
                break;
            case '('://读到括号就找到匹配的另一个括号后把整段送给下一层运算
                temp=i; i++; bas=1;
                while (bas!=0) {
                    if (st[i]=='(') bas++;
                    if (st[i]==')') bas--;
                    i++;
                }
                calc(temp+1,i-2,st,&temp);
                PushinNum(Numhead,temp,NULL);
                break;
            default://有可能碰到变量或者操作符，分别进行处理
                isvar=0; y=0; isope=0;
                strcpy(temps,st+i);
                if (temps[0]=='+'&&temps[1]=='+') {//特殊判断++ --两种操作符
                    temps[2]='\0'; i+=2;
                } else
                if (temps[0]=='-'&&temps[1]=='-') {
                    temps[2]='\0'; i+=2;
                } else
                for (x=0; x<strlen(temps); x++,i++) {//从该位置开始往后面循环判断
                    flag=0;
                    for (j=1; j<=K_all; j++)//判断一下是不是操作符中的字符
                        if (sope[j][x-y]==temps[x]) {
                            flag=1; isope=1; break;
                        }
                    if (flag==0) y++;//如果不是操作符就移一下位，保证对齐
                    if (flag==0&&x==0) isvar=1;//如果第一次就判断到不是操作符,那就只能是变量了
                    if ((flag==1&&isvar)||(isope&&!flag)||(isvar&&(temps[x]==')'||temps[x]==' '))||(!isvar&&(temps[x]>='0'&&temps[x]<='9'||temps[x]=='('||temps[x]==')'||temps[x]==' '))) {
                        temps[x]='\0';//判断如果已经满足是一个完整变量或者完整操作数就截断
                        break;
                    }
                }
                flag=0;
                for (x=1; x<=K_all; x++) {
                    if (!strcmp(sope[x],temps)) {//找一下是哪一个操作符，以方便进行优先级的判断
                        flag=1;
                        if (Opehead->next==NULL) {//第一个操作符先入栈
                            PushinOpe(Opehead,temps); break;
                        }
                        if (prior[x]<prior[Opehead->next->kind]) {//如果当前优先级更高，操作符就进栈
                            PushinOpe(Opehead,temps); break;
                        } else if (prior[x]>=prior[Opehead->next->kind]) {//如果当前优先级低，就取出两个操作数运算完后再进栈
                            temp=PopupOpe(Opehead);
                            PushinNum(Numhead,Operate(Numhead,Opehead,temp),NULL);
                            PushinOpe(Opehead,temps); break;
                            break;
                        }
                    }
                }
                if (!flag) {//如果没有这个操作符，那就是变量，进操作数栈
                    PushinNum(Numhead,0,temps);
                }
        }
    } while (i<=r);
    while (Opehead->next!=NULL) {//对所有没有运算完的部分继续运算完成
        temp=PopupOpe(Opehead);
        PushinNum(Numhead,Operate(Numhead,Opehead,temp),NULL);
    }
    *sum=Numhead->next->num;
}
int calculate(char *s)//对calc函数的简单调用，封装起来
{
    int res;
    calc(0,strlen(s)-1,s,&res);
    return res;
}
