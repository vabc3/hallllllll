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

int cmp(const void* a,const void* b)
{
	GG* ga=(GG*)a;
	GG* gb=(GG*)b;
	if(ga->t!=gb->t)
		return ga->t-gb->t;
	else if(ga->s!=gb->s)
		return gb->s-gb->s;
}

double measure()
{
	qsort(ca,n,sizeof(GG),cmp);


	int dt;
	int t=0;
	double v=0;
	double rt=0;
	int p;

	for(p=0;p<n;p++){
		int mb=ca[p].t+ca[p].d;
		int q;
		for(q=p+1;q<m;q++){
			if((ca[q].t<=mb)&&(mb<=ca[q].t+ca[q].d)){
				
			}
		}
	}

	if(n>0){
		for(p=0;p<n;p++){
			dt=ca[p].t-t;
			if(t<ca[p].t){
				rt+=v*dt+.5*a*dt*dt;
				v+=a*dt;
			}
printf("p=%d,v=%lf,rt=%lf,dt=%d\n",p,v,rt,dt);
			if(v>=ca[p].s){
//printf("fd");				
				dt=ca[p].d;
				v=ca[p].s;
				rt+=v*dt;
			}else{
				double rdt=1.0*(ca[p].s-v)/a;
printf("rdt=%lf\n",rdt);				
				dt=ca[p].d;
				if(dt>rdt){
					rt+=v*rdt+.5*a*rdt*rdt;
					v=ca[p].s;
					rt+=v*(dt-rdt);
				}else{
					rt+=v*dt+.5*a*dt*dt;
					v=v+a*dt;
				}
			}
			t=ca[p].t+ca[p].d;
		}
	}
printf("v=%lf,t=%d,rt=%lf\n",v,t,rt);
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

