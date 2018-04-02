#ifndef CREATNODE_H_INCLUDED
#define CREATNODE_H_INCLUDED

#include "define.h"

Statm* creatVoid();
Statm* creatInt(char* name, char* assignment);
Statm* creatBranch(char* judge,char*followStatm);
Statm* addInt();

#endif // CREATNODE_H_INCLUDED
