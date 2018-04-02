#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#define T_int 0
#define T_if      1
#define T_for     2
#define T_while   3
#define T_dowhile 4
#define T_break   5
#define T_printf  6
#define T_assign  7
#define T_else    8
#define T_empty   9

//变量定义
typedef struct value{
    int elem;
    struct value *next;
} Value;

typedef struct variable{
    char name[30];
    Value *val;
    struct variable *Lchild,*Rchild;
} Variable;

//单条语句储存定义
typedef struct statm{
    int type;
    int row;
    void *content;
    struct statm *next;
} Statm, *STATM;

//void 指针指向
typedef struct statm_int{
    char name[30];
    char assignment[50];
} Statm_int;

typedef struct statm_branch{
    char judge[50];
    char followStatm[50];
    Statm *bodyL;
    Statm *bodyR;
} Statm_branch;

#endif // DEFINE_H_INCLUDED
