#include<stdio.h>
#include<stdlib.h>

typedef struct node {
struct node * parent;
struct node * left ;
struct node * right;
int bf;
int data;
}node;
typedef node * avl;

void init();
void adjustbf();
void adjustimbalance();
void RR();
void LL();
void LR();
void RL();
int height();
void insert();
node *cnode();



