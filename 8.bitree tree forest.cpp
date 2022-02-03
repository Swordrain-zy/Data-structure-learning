#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
typedef struct BiTNode{
	int data;
	struct BitNode *LChild,*RChild;
}BiTNode,*BiTree;

typedef struct{
	BiTree Node[MaxSize];
	int top;
}SqStack;

void InitStack(SqStack &S){
	S.top=-1;
}

int visit(BiTree *T){printf("%d\n",(*T)->data);}

void InitStack(SqStack &S){
	S.top=-1;
}

bool StackEmpty(SqStack &S){
	if(S.top==-1)
		return true;
	else
		return false;
} 

bool Push(SqStack &S,BiTree x){
	if(S.top==MaxSize-1)
		return false;
	//S.top+=1;
	//S.data[S.top]=x;
	S.Node[++S.top]=x;
	return true;
} 
bool Pop(SqStack &S,BiTree x){
	if(S.top==-1)
		return false;
	x=S.Node[S.top--];
	//x=S.data[S.top];
	//S.top--;
} 
//从这开始往下看：
void PreOrder(BiTree *T){
	if(T!=NULL){
		visit(T);
		PreOrder((*T)->LChild);
		PreOrder((*T)->RChild);
	}
} 

void PreOrder2(BiTree T){
	SqStack S;
	InitStack(S);BiTree p=T;
	while(p||!StackEmpty(S)){
		if(p!=NULL){
			visit(p);
			Push(S,p);
			p=p->LChild;
		}
		else{
			Pop(S,p);
			p=p->RChild;
		}
	}
}

void InOrder(BiTree T){
	if(T!=NULL){
		InOrder(T->LChild);
		visit(T);
		InOrder(T->RChild);
	}
}  

void InOrder2(BiTree T){
	SqStack S;
	InitStack(S);BiTree p=T;
	while(p||!StackEmpty(S)){
		if(p!=NULL){
			Push(S,p);
			p=p->LChild;
		}
		else{
			Pop(S,p);visit(p);
			p=p->RChild;
		}
	}
} 

void PostOrder(BiTree T){
	if(T!=NULL){
		PostOrder(T->LChild);
		PostOrder(T->RChild);
		visit(T);
	}
}  
void PostOrder2(BiTree T){
	SqStack S;
	InitStack(S);BiTree p=T;//p->A
	while(p||!StackEmpty(S)){
		if(p!=NULL){
			Push(S,p);
			p=p->LChild;
		}
		else{
			Pop(S,p);
			visit(p->RChild);
			visit(p);
		}
	}
} 

typedef struct{
	BiTree data[MaxSize];
	int front,rear;
}SqQueue;

void InitQueue(SqQueue &Q){
	Q.rear=Q.front=0;
}

bool QueueEmpty(SqQueue Q){
	if(Q.rear==Q.front)
		return true;
	else
		return false;
}

bool EnQueue(SqQueue &Q,int x){
	if((Q.rear+1)%MaxSize==Q.front)
		return false;
	Q.data[Q.rear]->data=x;
	Q.rear=(Q.rear+1)%MaxSize;
	return true;
}

bool DeQueue(SqQueue &Q,int &x){
	if(Q.rear==Q.front)
		return false;
	x=Q.data[Q.front]->data;
	Q.front=(Q.front+1)%MaxSize;
	return true;
}

void LevelOrder(BiTree T){
	SqQueue Q;
	InitQueue(Q);
	BiTree p;
	EnQueue(Q,T);
	while(!IsEmpty(Q)){
		DeQueue(Q,p);
		visit(p);
		if(p->LChild!=NULL)
			EnQueue(Q,p->LChild);
		if(p->RChild!=NULL)
			EnQueue(Q,p->RChild);
		}
}

void CreateBiTree(BiTree *T){
	TreeElemtype ch;
	scanf("%c",&ch);
	if(ch=='#'){*T==NULL;}
	else{
		*T=(BiTree)malloc(sizeof(BitNode));
		if(!*T) return;
		else{
			(*T)->data=ch;
			CreateBiTree(&(*T)->LChild);
			CreateBiTree(&(*T)->RChild);
		}
	}
}

//Thread Tree:
typedef enum{Link,Thread}PTag;
//记住存储结构即可
typedef struct ThreadNode{
	int data;
	struct ThreadNode *lchild,*rchild;
	PTag ltag,rtag;
}ThreadNode,*ThreadTree;

ThreadTree pre;

void InThreading(ThreadTree p){
	if(p){
		InThreading(p->lchild);
		if(!p->lchild){
			p->ltag=Thread;
			p->lchild=pre;
		}
		if(!pre->rchild){
			pre->rtag=Thread;
			pre->rchild=p;
		}
		pre=p;
		InThreading(p->rchild);
	}
}

bool InOrderTraverse_Thr(ThreadTree T){
	ThreadTree p;
	p=T->lchild;
	while(p!=T){
		while(p->ltag==Link){p=p->lchild;}
		printf("%d",p->data);
		while(p->rtag==Thread&&p->rchild!=T){
			p=p->rchild;
			printf("%d",p->data);
		}
		p=p->rchild;
	}
	return true;
}

//BST:
typedef struct BSTNode{
	int data;
	struct BSTNode *lchild,*rchild;
}BSTNode, *BSTree;

bool BST_Search(BSTree T,int key,BSTree *t){
	if(T==NULL){return false;}
	else if(T->data==key){
		*t=T;
		return true;
	}
	else if(T->data>key){
		t=*T;
		BST_Search(T->lchild,key,t);
	}
	else{
		t=*T;
		BST_Search(T->rchild,key,t);
	}
}

bool BST_Insert(BSTree *T,int elem){
	BSTNode *s=(BSTNode*)malloc(sizeof(BSTNode));
	s->data=elem;
	s->lchild=NULL;
	s->rchild=NULL;
	BSTree *t=NULL;
	if(BST_Search(T,elem,t)){return false;}
	else{
		if(elem<(*t)->data){
			(*t)->lchild=s;
			return true;
		}
		else{
			(*t)->rchild=s;
			return true;
		}
	}
}

bool BST_Delete(BSTree *T,int key){
	if(!*T){return false;}
	else{
		if(key==(*T)->data){Delete(T);return true;}
		else if(key<(*T)->data){
			BST_Delete(&(*T)->lchild,key);
		}
		else{
			BST_Delete(&(*T)->rchild,key);
		}
	}
}

bool Delete(BSTree *p){
	BSTree q,s;
	if((*p)->lchild&&(*q).rchild){
		q=*p;s=q;
		while(q->rchild){
			s=q;
			q=q->rchild;
		}
		s->rchild=q->lchild;
		(*p)->data=q->data;
		free(q);
		return true;
	}
	else if((*p)->lchild||(*q).rchild){
		if((*p)->lchild){
			q=(*p)->lchild;
			(*p)->data=q->data;
			(*p)->lchild=q->lchild;
			(*p)->rchild=q->rchild;
			free(q);
		}
		else{
			q=(*p)->rchild;
			(*p)->data=q->data;
			(*p)->lchild=q->lchild;
			(*p)->rchild=q->rchild;
			free(q);
		}
	}
	else{
		free(p);return true;
	}
}

//AVL Tree:
typedef struct AVLNode{
	int data;
	int BF;
	struct AVLNode *lchild,*rchild;
}AVLNode,*AVLTree;

#define LH +1
#define EH 0
#define RH -1

void R_Rotate(AVLTree *T){
	AVLTree *p=(*T)->lchild;
	(*T)->lchild=(*p)->rchild;
	(*p)->rchild=(*T);
	*T=p;
}

void L_Rotate(AVLTree *T){
	AVLTree *p=(*T)->rchild;
	(*T)->rchild=(*p)->lchild;
	(*p)->lchild=(*T);
	*T=p;
}

void LeftBalance(AVLTree *T){
	AVLTree *p,*q;
	p=(*T)->lchild;
	switch((*p)->BF){
		case LH:
			R_Rotate(T);
			(*T)->BF=(*p)->BF=EH;
		case RH:
			q=(*p)->rchild;
			switch((*q)->BF){
				case LH:
					(*p)->BF=(*q)->BF=EH;(*T)->BF=RH;
					break;
				case RH:
					(*p)->BF=LH;(*q)->BF=(*T)->BF=EH;
					break;
			}
			L_Rotate(p);
			R_Rotate(T);
	}
}

void RightBalance(AVLTree *T){
	AVLTree *p,*q;
	p=(*T)->rchild;
	switch((*p)->BF){
		case RH:
			L_Rotate(T);
			(*T)->BF=(*p)->BF=EH;
		case LH:
			q=(*p)->lchild;
			switch((*q)->BF){
				case LH:
					(*p)->BF=RH;(*q)->BF=(*T)->BF=EH;
					break;
				case RH:
					(*p)->BF=(*q)->BF=EH;(*T)->BF=LH;
					break;
			}
			R_Rotate(p);
			L_Rotate(T);
	}
}

bool InsertAVL(AVLTree *T,int elem,bool *taller){
	if(!*T){
		(*T)=(AVLTree)malloc(sizeof(AVLNode));
		(*T)->data=elem;
		(*T)->lchild=(*T)->rchild=NULL;
		(*T)->BF=EH;
		*taller=true;
		return true;
	}
	else{
		if(elem==(*T)->data){return false;}
		if(elem<(*T)->data){
			if(InsertAVL((*T)->lchild,elem)==false){
				return false;
			}
			else{
				switch((*T)->BF){
					case LH:
						LeftBalance(T);
						*taller=false;
						break;
					case EH:
						(*T)->BF=LH;
						*taller=true;
						break;
					case RH:
						(*T)->BF=EH;
						*taller=false;
						break;
				}
			}
		}
		else{
			if(InsertAVL((*T)->rchild,elem)==false){
				return false;
			}
			else{
				switch((*T)->BF){
					case LH:
						(*T)->BF=EH;
						*taller=false;
						break;
					case EH:
						(*T)->BF=RH;
						*taller=true;
						break;
					case RH:
						RightBalance(T);
						*taller=false;
						break;
				}
			}
		}
	}
	return true;
}

void Build_AVLTree(int *a,int n){
	AVLTree T=NULL;
	bool taller;
	for(int i=0;i<n;i++){
		InsertAVL(&T,a[i],&taller);
	}
}




