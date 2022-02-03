#include <stdio.h>
#include <stdlib.h>

typedef struct LStack{
	int data;
	LStack *next;
}LStack,*LinkStack;

bool Push(LinkStack &S){	
	int x;
	LStack*r=S;
	scanf("%d",&x);
	while(x!=-1){
		LStack *s;
		s->data=x;
		s->next=r;
		r=s;
		scanf("%d",&x);
	}
	return true;
} 
//or
//s->data=x;
//s->next=S->next;
//S->next=s;
 
bool Pop(LinkStack &S,int &x){
	if(S->next==NULL){return false;}
	LStack *p=S;
	S=S->next;
	x=p->data;
	free(p);
	return true;
} 
//or
//p=S->next;
//S->next=p->next;
//x=p->data;
//free(p);
