#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 50
#define INITSIZE 100
typedef struct{
	int data[MAXSIZE];	
	int length;
}Sqlist;


typedef struct{
	int *data;
	int MaxSize;
	int Length;
}Seqlist; 


void IncreaseSize(Seqlist &L,int len){
	int *p=L.data;
	L.data=(int*)malloc((L.MaxSize+len)*sizeof(int));
	for(int i=0;i<L.Length;i++){
		L.data[i]=p[i];
	}
	L.MaxSize=L.MaxSize+len;
	free(p);
}

int InitList(Sqlist &L){
	int i;
	for(i=0;i<MAXSIZE;i++){
		L.data[i]=0;
	}
	L.length=0;
}

void InitList(Seqlist &L){
	L.data=(int*)malloc(MAXSIZE*sizeof(int));
	L.Length=0;
	L.MaxSize=MAXSIZE;
}


int Length(Sqlist L){
	int i; 
	for(i=0;i<MAXSIZE;i++){
		if(L.data[i]==-1)
			break;	
	}
	return i;
} 

int LocateElem(Sqlist L,int e){
	int i;
		for(i=0;i<L.length;i++){
		if(L.data[i]==e){
			i+=1;break; 
		}
	}
	if(i==L.length)
	i=0;
	return i;
}

int GetElem(Sqlist L,int i){
	int j;
	j=L.data[i-1];
	return j;
}

bool ListInsert(Sqlist &L,int i,int e){
	if(i<1||i>L.length+1){
		return false;
	}
	else if(L.length==MAXSIZE){
		return false;
	}
	else{
		int j;
		for(j=L.length;j>i-1;j--){
			L.data[j]=L.data[j-1];
		}
		L.data[j]=e;
		L.length++;	
	}
	return true;
	}
	
bool ListDelete(Sqlist &L,int i,int &e){
	bool judge;
	if(i<1||i>L.length){
		judge=0;
	}
	else{	
	e=L.data[i-1];
	for(;i<=L.length;i++){
		L.data[i-1]=L.data[i];
	}
	L.length--;
	judge=1;
	}
	return judge;
}

bool PrintList(Sqlist L){
	int i;
	for(i=0;i<L.length;i++){
		printf("%d ",L.data[i]);
	}
	return true;
}


