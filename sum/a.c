/*
 * =====================================================================================
 *       Filename:  a.c
 *        Created:  09/08/2012 09:12:57 PM
 *         Author:  Karata Lau (), vabc3h@gmail.com
 * =====================================================================================
 */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#define N 32
int n;
int a[N];
int b[N];
int lv,hv;

int cmp(const void* a,const void* b)
{
	return *(int*)a-*(int*)b;
}

int pir(int n,int k)
{
	if(k<0)
		return 0;
	else if(n==1){
		return (a[0]<=k)+1;
	}else{

		return pir(n-1,k)+pir(n-1,k-a[n-1]);
	}
}
int pmr(int n,int k)
{
	if(k<=0){
		int i=1;
		while(n--)i=i<<1;
		return i;
	}else{
		if(k>b[n-1])return 0;
	}
	if(n==1)
		return (a[0]>=k)+(k<=0);
	else{
		int x=pmr(n-1,k);
		int y=pmr(n-1,k-a[n-1]);
/*printf("%d,(%d)%d+(%d)%d=%d\n",n-1,k,x,k-a[n-1],y,x+y);*/
		return x+y;
	}
}

/*int pir2(int n,int up,int down)*/
/*{*/
/*    printf("%d,%d,%d\n",n,up,down);*/
/*    if(up<0)*/
/*        return 0;*/
/*    if(n==1){*/
/*        return ((n>=down) & (n<=up) ) + 1;*/
/*    }else{*/
/*        int x=pir2(n-1,up,down);*/
/*        int y=pir2(n-1,up-a[n-1],down-a[n-1]);*/
/*printf("%d(%d,%d)[%d]+(%d,%d)[%d]=%d\n",n-1,up,down,x,up-a[n-1],down-a[n-1],y,x+y);*/
/*        */
/*        return x+y;*/
/*    }*/
/*}*/

int measure()
{
	int i;
	int l1,l2;
	qsort(a,n,sizeof(int),cmp);
/*    for(i=0;i<n;i++)printf("%d.%d\n",i,a[i]);*/
	b[0]=a[0];
	for(i=1;i<n;i++)b[i]=b[i-1]+a[i];
/*    l2=pir(n,hv);*/
/*    l1=pir(n,lv-1);*/
	assert(hv!=0);
	assert(lv!=0);
/*    l2=pir2(n,hv,lv);*/
/*    l1=0;*/
	l2=pmr(n,lv);
	l1=pmr(n,hv+1);
/*printf("%d-%d\n",l2,l1);*/

	return l2-l1;
}

int main()
{
	FILE * pFile;
#ifdef KT
	char sysInputFile[] = "in";
#else
	char sysInputFile[] = "{sysFileUrl}";
#endif 
	pFile = fopen(sysInputFile, "r");
	int i;
	int m;
	fscanf(pFile,"%d",&m);
	while(m--){
		fscanf(pFile,"%d",&n);
		for(i=0;i<n;i++)
			fscanf(pFile,"%d",&a[i]);
		fscanf(pFile,"%d %d",&lv,&hv);
		printf("%d\n",measure());
	}
	fclose(pFile);
	return 0;
}

