#include <stdio.h>
#include "string_matching.h"


// Add any utility functions you need, eg Transition function for the Finite Automaton

int naive(char * text, char *pattern, int * indices){
	printf("Naive\t");
	int i, j;

	int k=0;
	int n=0;  //number of occurences

	int t=strlen(text);
	int p=strlen(pattern);
	for (i = 0; i <= t- p; i++) {
        for (j = 0; j < p; j++)
            if (text[i + j] != pattern[j])
                break;
 
        if (j == p) {
            //pattern found
			n++; //increase number of occurences
			indices[k]=i;         // add index 
			k++;
        }
    }
	
	return n;
}
static int* shifttable(char p[])
{
 int i,j,m;
 int *t=(int*)malloc(sizeof(int)*256);
 m=strlen(p);
 for(i=0;i<256;i++)
  t[i]=m;
 for(j=0;j<m-1;j++)
  t[p[j]]=m-1-j;
  return t;

}
static void lsp(char p[],int pi[])
{
int m=strlen(p),j=-1,i=1;
//int *pi=(int*)malloc(sizeof(int)*m);
pi[0]=-1;
for(i=1;i<m;i++)
{
	while(j>-1 && p[j+1]!=p[i])
		j=pi[j];
	if(p[j+1]==p[i])
		j++;
	pi[i]=j;
}
}
static int *good_suffix(char p[])
{
	int i,m = strlen(p);
	int kmp[m];
	lsp(p,kmp);
	int *gT = (int*)malloc(sizeof(int)*m);
	for(int k=1;k<m;k++)
	{	gT[k]=m-kmp[m-1]-1;
		for(i=m-2;i>=k-1;i--)
		{
		int j=0;
		while((j<k) && (p[i-j]==p[m-1-j])) j++;
		if(((i==k-1)&&(j==k))||((j==k)&&(p[i-j]!=p[m-1-j])))
		{
		gT[k]=m-1-i;
		break;}
		}
	}
return gT;

}
static void fnt(char p[],int tp[][256])
{	
	int m=strlen(p);
	int pi[m];
	lsp(p,pi);
	for(int i=0;i<256;i++)	tp[0][i]=0;
	tp[0][p[0]]=1;
	for(int i=1;i<=m;i++)
	{
	memcpy(tp[i],tp[pi[i-1]+1],255*sizeof(int));
	if(i!=m)
		tp[i][p[i]]=i+1;
	}

}

int horspool(char * text, char *pattern, int * indices){
	printf("Implement Horspool\t");
	int n=0;  //number of occurences

	 int i,j,k,m,t;
 j=0;
 t=strlen(text);
 m=strlen(pattern);
 i=m-1;
 int* table=shifttable(pattern);
 while(i<t)
 {
  k=0;
  while((k<m)&&(pattern[m-1-k]==text[i-k]))
   k++;
  if(k==m)
  {
   indices[j]=i-m+1;
   n++;
   j++;
   i+=table[text[i]];
  }
  else
   i+=table[text[i]];
 }
 	free(table);
	return n;
}

int boyerMoore( char * text, char *pattern, int * indices){
	printf("Implement Boyer Moore\t");
	int n=0;  //number of occurences
	int *sT=shifttable(pattern);
	int *gT = good_suffix(pattern);
	int i,j,k,t=strlen(text),m=strlen(pattern);
	i=m-1;
	while(i<t)
	{
		j=0;
		while((j<m) && (text[i-j]==pattern[m-1-j])) j++;
		if(j==m){
		    indices[n++]=i-m+1;
		    i+=sT[text[i]];		
		}
		else{
		int d1=((sT[text[i-j]]-j)>1)?(sT[text[i-j]]-j):1;
		if(j>0){
		int d2=gT[j];
		d1=d1>d2?d1:d2;
		}
		i+=d1;
		}
	}
free(gT);
free(sT);
	return n;
}

int rabinKarp( char * text, char *pattern, int * indices){
	printf("Implement Rabin Karp\t");
	int i,n=0;  //number of occurences
	int m=strlen(pattern),t_n=strlen(text);
	int p=0,t=0,h=1,d=256,q = 12289;
	for(i=0;i<m-1;i++)
	{
	h=(h*d)%q;//computing d^m-1 mod q
	}
	for(i=0;i<m;i++)
	{
		p=(d*p+pattern[i])%q;
		t=(d*t+text[i])%q;
	}
	for(int s=0;s<=(t_n-m);s++)
	{
		if(p==t){
			int j=0;
			while(j<m && (pattern[j]==text[s+j]))j++;
			if(j==m)	
			    indices[n++]=s;		
		}
		if(s<(t_n-m))
			t=((t-h*text[s])*d+text[s+m])%q;
		if(t<0)
			t+=q;
	}
	return n;
}

int finiteAutomaton( char * text, char *pattern, int * indices){
	printf("Implement Finite Automaton based search\t");
	int n=0,t=strlen(text),m=strlen(pattern),q=0;  //number of occurences
	int tp[m+1][256]; 
	fnt(pattern,tp);
	for(int i=0;i<t;i++)
	{
		q = tp[q][text[i]];
		if(q==m)
		{
			indices[n++]=i-m+1;
		}
	}
	return n;
}

int KMP( char * text, char *pattern, int * indices){
    printf("Implement KMP\t");
  int n=0;  //number of occurences
  int t=strlen(text),m=strlen(pattern),i=0,q=-1;
  int pi[m];
  lsp(pattern,pi);
for(i=0;i<t;i++)
{
	while(q>-1 && pattern[q+1]!=text[i])
		q=pi[q];
	if(pattern[q+1]==text[i])
		q++;
	if(q==m-1)
	{
	indices[n++]=i-m+1;
	q=pi[q];
	}
}
//free(pi);
  return n;
}
