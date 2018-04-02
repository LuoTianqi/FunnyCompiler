#ifndef __CALC_H
#define __CALC_H

#include "define.h"

#define K_all       15
#define K_Plus      1
#define K_Minus     2
#define K_Multiply  3
#define K_Divide    4
#define K_Inc       5
#define K_Dec       6
#define K_And       7
#define K_Or        8
#define K_Equal     9
#define K_Unequal   10
#define K_Greater   11
#define K_Smaller   12
#define K_GreaterEqual  13
#define K_SmallerEqual  14
#define K_Assign    15

typedef struct ope{
    char ope[3];
    int kind;
    struct ope *next;
} Ope;
typedef struct num{
    int num;
    char var[32];
    struct num *next;
} Num;
char *IntToStr(int x);
double StrToInt(char *s);
void PushinNum(Num* Numhead,int x,char *name);
void PopupNum(Num *Numhead,int *x,Value **p);//如果栈顶为变量则从p输出Value，从x输出值，如果为常数，则只从x输出
void PushinOpe(Ope* Opehead,char *s);
int PopupOpe(Ope *Opehead);
int calculate(char *s);
#endif
