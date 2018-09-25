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
static int* lsp(char p[])
{
int m=strlen(p),j=-1,i=1;
int *pi=(int*)malloc(sizeof(int)*m);
pi[0]=-1;
for(i=1;i<m;i++)
{
	while(j>-1 && p[j+1]!=p[i])
		j=pi[j];
	if(p[j+1]==p[i])
		j++;
	pi[i]=j;
}
return pi;
}
static int **fnt(char p[])
{	
	int m=strlen(p);
	int **tp = (int**)calloc(m+1,sizeof(int*));
	int *pi = lsp(p);
	tp[0]=(int*)calloc(255,sizeof(int));
	tp[0][p[0]]=1;
	for(int i=1;i<=m;i++)
	{
	tp[i]=(int*)calloc(255,sizeof(int));
	memcpy(tp[i],tp[pi[i-1]+1],255*sizeof(int));
	if(i!=m)
		tp[i][p[i]]=i+1;
	}
free(pi);
return tp;
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
	return n;
}

int rabinKarp( char * text, char *pattern, int * indices){
	printf("Implement Rabin Karp\t");
	int n=0;  //number of occurences
	return n;
}

int finiteAutomaton( char * text, char *pattern, int * indices){
	printf("Implement Finite Automaton based search\t");
	int n=0,t=strlen(text),m=strlen(pattern),q=0;  //number of occurences
	int **tp = fnt(pattern);
	for(int i=0;i<t;i++)
	{
		q = tp[q][text[i]];
		if(q==m)
		{
			indices[n++]=i-m+1;
		}
	}
	for(int i=0;i<=m;i++)
	free(tp[i]);
	free(tp);
	return n;
}

int KMP( char * text, char *pattern, int * indices){
    printf("Implement KMP\t");
  int n=0;  //number of occurences
  int t=strlen(text),m=strlen(pattern),i=0,q=-1;
  int *pi=lsp(pattern);
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
free(pi);
  return n;
}
