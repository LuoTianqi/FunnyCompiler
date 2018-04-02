#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operate.h"
#include "define.h"
/*
本段代码为通过二叉排序树对当前申请的变量进行储存，并根据当前执行
的代码域对同名变量储存值进行用链栈储存。
*/
extern Variable* VARhead;
Value* NewVar(char *name)
{
    Variable *p,*q;//查找是否已经存在同名的变量
    int res=0;
    p=VARhead;
    while (p!=NULL) {
        res=strcmp(name,p->name);
        if (res==-1) {q=p; p=p->Lchild;}
        else if (res==1) {q=p; p=p->Rchild;}
        else if (res==0) break;
    }
    if (res==0&&VARhead!=NULL) {//已经存在同名变量
        Value *q=(Value*)malloc(sizeof(Value)),*t=p->val;
        q->elem=0;
        p->val=q;
        q->next=t;//对已经存在的变量进行进栈
        return p->val;
    } else {//新变量，新建树节点
        p=(Variable*)malloc(sizeof(Variable));
        strcpy(p->name,name);//对变量进行初始化
        p->val=(Value*)malloc(sizeof(Value));
        p->val->elem=0;
        p->val->next=NULL;
        p->Lchild=p->Rchild=NULL;
        if (res==-1) q->Lchild=p;
        else if (res==1) q->Rchild=p;
        if (VARhead==NULL) VARhead=p;
        return p->val;
    }
}
void DeleteVar(char *name)
{
    Variable *p=VARhead,*q=NULL;
    Value *t;
    int res;
    while (p!=NULL) {
        res=strcmp(name,p->name);
        if (res==-1) {q=p; p=p->Lchild;}
        else if (res==1) {q=p; p=p->Rchild;}
        else if (res==0) break;
    }
    if (p==NULL) return; //没有这个变量
    t=p->val->next;
    free(p->val);
    p->val=t;//先将栈顶出栈

    if (p->val==NULL) {
        if (q==NULL) {
            free(p);
            VARhead=NULL;
        } else {
            //分三种情况：一是只有左子树：
            if (p->Lchild&&!p->Rchild) {
                if (q->Lchild==p) q->Lchild=p->Lchild;
                else if (q->Rchild==p) q->Rchild=p->Lchild;
            } else //二是只有右子树
            if (p->Rchild&&!p->Lchild) {
                if (q->Lchild==p) q->Lchild=p->Rchild;
                else if (q->Rchild==p) q->Rchild=p->Rchild;
            } else {//三是左右皆有子树,将左子树代替原节点，右子树加到左子树最右边
                Variable *t;
                if (q->Lchild==p) q->Lchild=p->Lchild;
                else if (q->Rchild==p) q->Rchild=p->Lchild;
                t=p->Lchild;
                while (t->Rchild!=NULL) t=t->Rchild;
                t->Rchild=p->Rchild;
            }
            free(p);
        }
    }//如果变量栈已经全空了，就将变量删除。
}
void AssignVar(char *name,int x)
{
    Value *p=FindVar(name);
    if (p!=NULL) p->elem=x;
}
Variable *FindVarHead(char *name)
{
    Variable *p=VARhead;
    int res;
    while (p!=NULL) {
        res=strcmp(name,p->name);
        switch (res) {
            case 0:
                return p;
                break;
            case -1:
                p=p->Lchild;
                break;
            case 1:
                p=p->Rchild;
                break;
        }
    }
    return NULL;
}
Value* FindVar(char *name)
{
    Variable *p=VARhead;
    int res;
    while (p!=NULL) {
        res=strcmp(name,p->name);
        switch (res) {
            case 0:
                return p->val;
                break;
            case -1:
                p=p->Lchild;
                break;
            case 1:
                p=p->Rchild;
                break;
        }
    }
    return NULL;
}
void FreeVar(Variable *p)
{
    if (p==NULL) return;
    FreeVar(p->Lchild);
    FreeVar(p->Rchild);
    free(p);
}
int PrintVar(Variable *p,int x,int level,char name[][30],int a[])
{
    int x1,x2;
    if (p==NULL) return 0;
    strcpy(name[x],p->name);
    a[x]=p->val->elem;
    x1=PrintVar(p->Lchild,2*x,level+1,name,a);
    x2=PrintVar(p->Rchild,2*x+1,level+1,name,a);
    x1=x1>x?x1:level;
    x2=x1>x2?x1:x2;
    return x2;
}
