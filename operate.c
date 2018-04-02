#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operate.h"
#include "define.h"
/*
���δ���Ϊͨ�������������Ե�ǰ����ı������д��棬�����ݵ�ǰִ��
�Ĵ������ͬ����������ֵ��������ջ���档
*/
extern Variable* VARhead;
Value* NewVar(char *name)
{
    Variable *p,*q;//�����Ƿ��Ѿ�����ͬ���ı���
    int res=0;
    p=VARhead;
    while (p!=NULL) {
        res=strcmp(name,p->name);
        if (res==-1) {q=p; p=p->Lchild;}
        else if (res==1) {q=p; p=p->Rchild;}
        else if (res==0) break;
    }
    if (res==0&&VARhead!=NULL) {//�Ѿ�����ͬ������
        Value *q=(Value*)malloc(sizeof(Value)),*t=p->val;
        q->elem=0;
        p->val=q;
        q->next=t;//���Ѿ����ڵı������н�ջ
        return p->val;
    } else {//�±������½����ڵ�
        p=(Variable*)malloc(sizeof(Variable));
        strcpy(p->name,name);//�Ա������г�ʼ��
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
    if (p==NULL) return; //û���������
    t=p->val->next;
    free(p->val);
    p->val=t;//�Ƚ�ջ����ջ

    if (p->val==NULL) {
        if (q==NULL) {
            free(p);
            VARhead=NULL;
        } else {
            //�����������һ��ֻ����������
            if (p->Lchild&&!p->Rchild) {
                if (q->Lchild==p) q->Lchild=p->Lchild;
                else if (q->Rchild==p) q->Rchild=p->Lchild;
            } else //����ֻ��������
            if (p->Rchild&&!p->Lchild) {
                if (q->Lchild==p) q->Lchild=p->Rchild;
                else if (q->Rchild==p) q->Rchild=p->Rchild;
            } else {//�������ҽ�������,������������ԭ�ڵ㣬�������ӵ����������ұ�
                Variable *t;
                if (q->Lchild==p) q->Lchild=p->Lchild;
                else if (q->Rchild==p) q->Rchild=p->Lchild;
                t=p->Lchild;
                while (t->Rchild!=NULL) t=t->Rchild;
                t->Rchild=p->Rchild;
            }
            free(p);
        }
    }//�������ջ�Ѿ�ȫ���ˣ��ͽ�����ɾ����
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
