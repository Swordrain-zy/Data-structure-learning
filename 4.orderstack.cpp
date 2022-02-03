
#define MaxSize 10
typedef struct{
	int data[MaxSize];
	int top;
}SqStack;

void InitStack(SqStack &S){
	S.top=-1;
}

bool StackEmpty(SqStack &S){
	if(S.top==-1)
		return true;
	else
		return false;
} 

bool Push(SqStack &S,int x){
	if(S.top==MaxSize-1)
		return false;
	//S.top+=1;
	//S.data[S.top]=x;
	S.data[++S.top]=x;
	return true;
} 
bool Pop(SqStack &S,int &x){
	if(S.top==-1)
		return false;
	x=S.data[S.top--];
	//x=S.data[S.top];
	//S.top--;
} 

bool GetTop(SqStack S,int &x){
	if(S.top==-1)
		return false;
	x=S.data[S.top];
	return true;
} 

#define MaxSize 10
typedef struct{
	int data[MaxSize];
	int top0;
	int top1;
}ShStack; 

void InitShStack(ShStack &S){
	S.top0=-1;
	S.top1=MaxSize;
}

bool Sh_Push(ShStack &S,int num,int elem){
	if(num==0){
		if(S.top0+1!=S.top1){S.data[++S.top0]=elem;}
		else{return false;}
	}
	else{
		if(S.top1-1!=S.top0){S.data[--S.top1]=elem;}
		else{return false;}
	}
	return true;
}

bool Sh_Pop(ShStack &S,int num,int &x){
	if(num==0){
		if(S.top0==-1){return false;}
		else{x=S.data[S.top0--];}
	}
	else{
		if(S.top1==MaxSize){return false;}
		else{x=S.data[S.top1++];}
	}
	return true;
}