#define MAXLEN 100
typedef struct{
	char ch[MAXLEN];
	int length;
}SString; 
//return sub string:
bool SubString(SString &Sub,SString S,int pos,int len){
	if(pos+len-1>S.length){
		return false;
	}
	for (int i=pos;i<pos+len;i++){ 
		Sub.ch[i-pos+1]=S.ch[i];
		Sub.length=len;
	}
	return true;
}
//string compare
int StrCompare(SString S,SString T){
	for(int i=1;i<=S.length && i<=T.length;i++){
		if(S.ch[i]!=T.ch[i])
			return S.ch[i]-T.ch[i];
	}
	return S.length-T.length;
}
 
int StrLength(SString S){
	int i;
	for(i=0;S.ch[i]!='\0';i++){
	}
	i++;
	return i;
}

int Index(SString S,SString T){
 	int i=1,n=StrLength(S),m=StrLength(T);
 	SString sub;
 	while(i<=n-m+1){
 		SubString(sub,S,i,m);
 		if(StrCompare(sub,T)!=0)
		 	++i;//i++
		else return i;
	 }
	 return 0;
 } 

int Index(SString S,SString T){
	int i=1,j=1;
	while(i<=S.length && j<=T.length){
		if(S.ch[i]==T.ch[j]){ 
			++i;
			++j;
		}
		else{
			i=i-j+2;
			j=1;
		}
	} 
	if(j>T.length)
		return i-T.length;
	else
		return 0;
} 
//KMP:

void Get_Next(SString T,int *next){
	int i,j;
	i=1;j=0;next[1]=0;
	while(i<T.length){
		if(j==0||T.ch[i]==T.ch[j]){
			i++;j++;
			next[i]=j;
		}
		else{
			j=next[j];
		}
	}
}

int Index_KMP(SString S,SString T,int pos){
	int i=pos;
	int j=1;
	int next[255];
	Get_Next(T,next);
	while(i<=S.length&&i<=T.length){
		if(j==0||S.ch[i]==T.ch[j]){
			i++;j++;
		}
		else{
			j=next[j];
		}
	}
	if(j>T.length){
		return i-T.length;
	}
	else{return 0;}
}

 void Get_Nextval(SString T,int *nextval){
	int i,j;
	i=1;j=0;nextval[1]=0;
	while(i<T.length){
		if(j==0||T.ch[i]==T.ch[j]){
			i++;j++;
			if(T.ch[i]!=T.ch[j]){nextval[i]=j;}
			else{nextval[i]=nextval[j];}
		}
		else{
			j=nextval[j];
		}
	}
}
























