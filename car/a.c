#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#define N 52

int n;
int a;
int T;
typedef struct gg
{
	int s,t,d;
}GG;

GG ca[N];
int cd[N*2];

int cmp(const void* a,const void* b)
{
	GG* ga=(GG*)a;
	GG* gb=(GG*)b;
	if(ga->t!=gb->t)
		return ga->t-gb->t;
	else if(ga->s!=gb->s)
		return gb->s-gb->s;
}

int cm(const void* a,const void* b){
	return *(int*)a-*(int*)b;
}
#define V 10000
double getV(int t){
	int i;
	double min=V;
	for(i=0;i<n;i++){
		if(ca[i].t<=t && t<ca[i].t+ca[i].d)
			if(ca[i].s<min){
				min=ca[i].s;
			}
	}
	return min;
}

double measure()
{
	qsort(ca,n,sizeof(GG),cmp);
	int i;
	int j=0;
	for(i=0;i<n;i++){
		cd[j++]=ca[i].t;
		if(cd[j-1]>T)cd[j-1]=T;
		cd[j++]=ca[i].t+ca[i].d;
		if(cd[j-1]>T)cd[j-1]=T;
	}
	qsort(cd,n*2,sizeof(int),cm);
/*for(i=0;i<n*2;i++)printf("%d\n",cd[i]);*/
	int dt;
	int t=0;
	double v=0;
	double rt=0;
	int p;
	double tv;
	for(i=0;i<2*n;i++){
/*printf("cd=%d,t=%d\n",cd[i],t);	*/
//		if(cd[i]>=T)break;

		dt=cd[i]-t;
/*if(cd[i]>=T && dt==0)break;		*/
		tv=getV(t);
/*printf("rt=%lf,t=%d,tv=%lf\n",rt,t,tv);*/
		if(tv==V){
//printf("jer");			
			rt+=v*dt+.5*a*dt*dt;
			v+=a*dt;
		}else if(v>=tv){
			rt+=tv*dt;
			v=tv;
		}else{
			double rdt=1.0*(tv-v)/a;
			if(dt>rdt){
				rt+=v*rdt+.5*a*rdt*rdt;
				v=tv;
				rt+=v*(dt-rdt);
			}else{
				rt+=v*dt+.5*a*dt*dt;
				v=v+a*dt;
			}
		}
		t=cd[i];
	}
	if(t<T){
		dt=T-t;
		rt+=v*dt+.5*a*dt*dt;
	}

	return rt;
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
			fscanf(pFile,"%d%d%d",&ca[i].s,&ca[i].t,&ca[i].d);
		fscanf(pFile,"%d %d",&T,&a);
		printf("%.4lf\n",measure());
	}
	fclose(pFile);
	return 0;
}

