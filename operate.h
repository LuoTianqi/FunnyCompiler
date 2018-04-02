#ifndef __OPERATE_H
#define __OPERATE_H

#include "define.h"
Value* NewVar(char *name);          //定义新变量
void DeleteVar(char *name);         //删除变量
void AssignVar(char *name,int x);   //变量赋值
Variable *FindVarHead(char *name);  //查找变量链表
Value* FindVar(char *name);         //查找变量的栈顶
void FreeVar(Variable *p);          //释放所有变量
int PrintVar(Variable *p,int x,int level,char name[][30],int a[]);   //输出变量树，用于调试
#endif
