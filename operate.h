#ifndef __OPERATE_H
#define __OPERATE_H

#include "define.h"
Value* NewVar(char *name);          //�����±���
void DeleteVar(char *name);         //ɾ������
void AssignVar(char *name,int x);   //������ֵ
Variable *FindVarHead(char *name);  //���ұ�������
Value* FindVar(char *name);         //���ұ�����ջ��
void FreeVar(Variable *p);          //�ͷ����б���
int PrintVar(Variable *p,int x,int level,char name[][30],int a[]);   //��������������ڵ���
#endif
