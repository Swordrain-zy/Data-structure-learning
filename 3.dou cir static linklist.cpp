#include<stdio.h>
#include<stdlib.h>
//double linked list:
typedef struct DNode{
	int data;
	struct DNode *prior,*next;
}DNode,*DLinkList;

bool InitDLinklist(DLinkList &L){
	L=(DNode*)malloc(sizeof(DNode));
	if(L==NULL)
		return false;
	L->prior=NULL;
	L->next=NULL;
	return true;
} 

bool Empty(DLinkList L){
	if(L->next==NULL)
		return true;
	else
		return false;
}

bool InsertDNode(DNode *p,DNode *s){
	s->next=p->next;
	if(p->next!=NULL)
	 	p->next->prior=s;
	s->prior=p;
	p->next=s;
} 

bool DeleteDNode(DNode *p){
	if(p->next==NULL)
		return false;
	DNode *q=p->next;
	p->next=q->next;
	if(q->next!=NULL)
		q->next->prior=p;
	free(q);
	return true;
} 

void DestoryList(DLinkList &L){
	while(L->next!=NULL){
		DeleteDNode(L);
	}
		free(L);
		L=NULL;
} 

void PrintDNode(DLinkList L){
	DNode *p=L;
	while(p!=NULL){
		printf("%d ",p->data);
		p=p->next; 
	}
}
//circular linked list:
typedef struct LNode{
	int data;           
	struct LNode *next;
}LNode,*LinkList; 

bool InitList(LinkList &L){
	L=(LNode*)malloc(sizeof(LNode));
	if(L==NULL)
		return false;
	L->next=L;
	return true; 
} 

bool InitDLinklist(DLinkList &L){
	L=(DNode*)malloc(sizeof(DNode));
	if(L==NULL)
		return false;
	L->prior=L;
	L->next=L;
	return true;
} 

bool Empty(DLinkList L){
	if(L->next==L)
		return true;
	else
		return false;
} 

//static linklist:
#define MaxSize 10
typedef struct Node{
	int data;
	int next;
}StaticLinkList;
StaticLinkList s[MaxSize];

bool List_Init(StaticLinkList *s){
	s[0].data=-1;
	for(int i=0;i<MaxSize;i++){
		s[i].next=i+1;
	}
	s[MaxSize-1].next=-1;
	return true;
}
int List_Length(StaticLinkList *s){
	int cnt=0;
	if(s[0].data==-1){return cnt;}
	else{
		int tag=s[0].data;
		while(tag!=-1){
			tag=s[tag].next;
			cnt++;}
	}
	return cnt;
}
//insert and delete of static linklist:
bool List_Insert(StaticLinkList *s,int i,int elem){
	if(i<1||i>List_Length(s)+1) {return false;}
	if(s[0].next==-1) {return false;}
	if(s[0].data==-1){
		int tag2=s[0].next;
		s[0].data=tag2;
		s[0].next=s[tag2].next;
		s[tag2].data=elem;
		s[tag2].next=-1;
		return true;
	}
	int cnt=0,tag=0,tag1=s[0].data,tag2=s[0].next;
	while(cnt<i){
		cnt++;
		if(cnt<i) {tag=tag1; tag1=s[tag1].next;}
	}
	s[tag2].data=elem;
	s[0].next=s[tag2].next;
	s[tag2].next=tag1;
	if(tag!=0) {s[tag].next=tag2;}
	else {s[0].data=tag2;}
	return true;
}

bool List_Delete(StaticLinkList *s,int i,int &x){
	if(i<1||i>List_Length(s)) {return false;}
	if(s[0].data==-1) {return false;}
	if(List_Length(s)==1){
		x=s[s[0].data].data;
		s[s[0].data].next=s[0].next;
		s[0].next=s[0].data;
		s[0].data=-1;
		return true;
	}
	int cnt=0,tag=0,tag1=s[0].data,tag2=s[0].next;
	while(cnt<i){
		cnt++;
		if(cnt<i) {tag=tag1; tag1=s[tag1].next;}
	}
	s[tag].next=s[tag1].next;
	x=s[tag1].data;
	s[tag1].next=tag2;
	s[0].next=tag1;
	return true;
}



































