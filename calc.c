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
int Operate(Num *Numhead,Ope *Opehead,int temp)//����������������㷽ʽ�ֱ��������
{
    int x1,x2;
    Value *p1,*p2;
    if (temp==K_Inc) {//��Ϊ++ --��ı���������Ե������������ж�
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
    Num *Numhead;//������
    Ope *Opehead;//������
    int i,j,bas,temp,x,y,flag,isvar,isope;
    char temps[25];
    Numhead=(Num*)malloc(sizeof(Num));//����ջͷ
    Numhead->num=0;
    strcpy(Numhead->var,"");
    Numhead->next=NULL;
    Opehead=(Ope*)malloc(sizeof(Ope));//����ջͷ
    Opehead->next=NULL;
    strcpy(Opehead->ope,"");
    Opehead->kind=0;
    i=l; j=r; *sum=0; st[r+1]='\0';
    do {
        switch (st[i]) {
            case ' '://�ո�����
                i++;
                break;
            case '0':case '1':case '2':case '3':case '4':case '5'://��������ջ
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
            case '('://�������ž��ҵ�ƥ�����һ�����ź�������͸���һ������
                temp=i; i++; bas=1;
                while (bas!=0) {
                    if (st[i]=='(') bas++;
                    if (st[i]==')') bas--;
                    i++;
                }
                calc(temp+1,i-2,st,&temp);
                PushinNum(Numhead,temp,NULL);
                break;
            default://�п��������������߲��������ֱ���д���
                isvar=0; y=0; isope=0;
                strcpy(temps,st+i);
                if (temps[0]=='+'&&temps[1]=='+') {//�����ж�++ --���ֲ�����
                    temps[2]='\0'; i+=2;
                } else
                if (temps[0]=='-'&&temps[1]=='-') {
                    temps[2]='\0'; i+=2;
                } else
                for (x=0; x<strlen(temps); x++,i++) {//�Ӹ�λ�ÿ�ʼ������ѭ���ж�
                    flag=0;
                    for (j=1; j<=K_all; j++)//�ж�һ���ǲ��ǲ������е��ַ�
                        if (sope[j][x-y]==temps[x]) {
                            flag=1; isope=1; break;
                        }
                    if (flag==0) y++;//������ǲ���������һ��λ����֤����
                    if (flag==0&&x==0) isvar=1;//�����һ�ξ��жϵ����ǲ�����,�Ǿ�ֻ���Ǳ�����
                    if ((flag==1&&isvar)||(isope&&!flag)||(isvar&&(temps[x]==')'||temps[x]==' '))||(!isvar&&(temps[x]>='0'&&temps[x]<='9'||temps[x]=='('||temps[x]==')'||temps[x]==' '))) {
                        temps[x]='\0';//�ж�����Ѿ�������һ�������������������������ͽض�
                        break;
                    }
                }
                flag=0;
                for (x=1; x<=K_all; x++) {
                    if (!strcmp(sope[x],temps)) {//��һ������һ�����������Է���������ȼ����ж�
                        flag=1;
                        if (Opehead->next==NULL) {//��һ������������ջ
                            PushinOpe(Opehead,temps); break;
                        }
                        if (prior[x]<prior[Opehead->next->kind]) {//�����ǰ���ȼ����ߣ��������ͽ�ջ
                            PushinOpe(Opehead,temps); break;
                        } else if (prior[x]>=prior[Opehead->next->kind]) {//�����ǰ���ȼ��ͣ���ȡ��������������������ٽ�ջ
                            temp=PopupOpe(Opehead);
                            PushinNum(Numhead,Operate(Numhead,Opehead,temp),NULL);
                            PushinOpe(Opehead,temps); break;
                            break;
                        }
                    }
                }
                if (!flag) {//���û��������������Ǿ��Ǳ�������������ջ
                    PushinNum(Numhead,0,temps);
                }
        }
    } while (i<=r);
    while (Opehead->next!=NULL) {//������û��������Ĳ��ּ����������
        temp=PopupOpe(Opehead);
        PushinNum(Numhead,Operate(Numhead,Opehead,temp),NULL);
    }
    *sum=Numhead->next->num;
}
int calculate(char *s)//��calc�����ļ򵥵��ã���װ����
{
    int res;
    calc(0,strlen(s)-1,s,&res);
    return res;
}
