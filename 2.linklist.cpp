#include<stdio.h>
#include<stdlib.h>

typedef struct LNode{
	int data;           
	struct LNode *next;
}LNode,*LinkList;

bool InitList(LinkList &L) {  
	L=NULL;
	return true;
}

bool Empty(LinkList L){ 
	if(L==NULL){
		return true;
	}
	else{
		return false;
	}            
}

bool Initlist(LinkList &L){ 
	L=(LNode*)malloc(sizeof(LNode));
	if(L==NULL) return false;
	else L->next=NULL;
	return true;
}

LNode *GetElem(LinkList L,int i){
	int j;
	LNode *p=L->next;
	if(i==0)
	return L;
	if(i<1)
	return NULL; 
	while(p&&j<i){
		p=p->next;
		j++;
	}
	return p;
}

LNode *LocateElem(LinkList L,int e){
	LNode *p=L->next;
	while(p!=NULL&&p->data!=e){
		p=p->next;
	}
	return p;
}

bool PutElem(LinkList L,int i,int x){
	LNode *p=GetElem(L,i-1);//find i-1;
	LNode *s=(LNode*)malloc(sizeof(LNode));
	s->data=x;
	s->next=p->next;
	p->next=s;
	return true;
}
bool PutElem(LNode* L, LNode* s) {
	s->next=L->next;
	L->next=s;
	int t;
	t=s->data;
	s->data=L->data;
	L->data=t;
	return true;
}

bool DeleteElem(LinkList L,int i){
	LNode *p=GetElem(L,i-1);
	LNode* q=p->next;
	p->next=q->next;
	free(q);
	return true;
}

//q=p->next
//p->data=p->next->data
//p->next=q->next
//free(q)

int length(LinkList L){
	int len=0;
	LNode *p=L;
	while(p->next!=NULL){
		p=p->next;
		len++;
	}
	return len;
} 

bool ListInsert(LinkList &L,int i,int e){
	if(i<1)
	return false;
	LNode *p;
	int j=0;
	p=L;
	while(p!=NULL&&j<i-1){
		p=p->next;
		j++;
	}
	if(p==NULL){
		return false;
	}
	LNode *s=(LNode*)malloc(sizeof(LNode));
	s->data=e;
	s->next=p->next;
	p->next=s;
	return true;
} 

LinkList List_TailInsert(LinkList&L){
	int x;
	L=(LinkList)malloc(sizeof(LNode));
	LNode *s,*r=L;
	scanf("%d",&x);
	while(x!=9999){
		s=(LNode*)malloc(sizeof(LNode));
		s->data=x;
		r->next=s;
		r=s;
		scanf("%d",&x);
	}
	r->next=NULL;
	return L;
} 

LinkList List_HeadInsert(LinkList&L){
	int x;
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL; 
	LNode *s;
	scanf("%d",&x);
	while(x!=9999){
		s=(LNode*)malloc(sizeof(LNode));
		s->data=x;
		s->next=L->next;
		L->next=s; 
		scanf("%d",&x);
	}
	return L;
}




















 
