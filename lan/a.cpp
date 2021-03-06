/*Sample code to read in test cases:*/
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

class PT
{
public:
	PT(int a,int b):x(a),y(b)
	{
		mark=false;
	}
	int x,y;
	bool mark;

};

int n;
vector<PT> s;

double getK(const PT& a,const PT&b){
	return 1.0*(b.y-a.y)/(b.x-a.x);
}

double getX(const PT& a,const PT&b,const PT&c){
	int x1=a.x-b.x;
	int y1=a.y-b.y;
	int x2=c.x-b.x;
	int y2=c.y-b.y;
	return (x1*x2+y1*y2)/sqrt((x1*x1+y1*y1)*(x2*x2+y2*y2));
}


void show(int k){
	cout<<s[k].x<<" "<<s[k].y<<endl;
	s[k].mark=true;
}


void doi(){
	int i;
	int mp=0;
	int min=s[0].x;
	for(i=1;i<n;i++){
		if(s[i].x<min){
			min=s[i].x;
			mp=i;
		}
	}
	show(mp);
double ma=-numeric_limits<double>::infinity();
double tmp;
int pre=mp;
	mp=0;
	for(i=0;i<n;i++){
		if(s[i].mark)continue;
		tmp=getK(s[pre],s[i]);
		if(ma<tmp){ma=tmp;mp=i;}
	}
	show(mp);

	int cou=n-2;
	int fa=pre;
	int fb=mp;
	double kn;

	double tg;
	while(cou){
		kn=getK(s[fa],s[fb]);
		ma=numeric_limits<double>::infinity();
		mp=-1;
		for(i=0;i<n;i++){
			if(s[i].mark)continue;
//            tmp=getK(s[fb],s[i]);
//            if(tmp==-numeric_limits<double>::infinity()){mp=i;break;}
//cout<<tmp<<","<<kn<<endl;			
//            tg=(tmp-kn)/(1+tmp*kn);
//            if(tg<0)tg=-tg;
            tg=getX(s[fa],s[fb],s[i]);
//cout<<tg<<endl;
			if(tg<ma){ma=tg;mp=i;}
		}

		show(mp);
		fa=fb;
		fb=mp;
		cou--;
	}
}

int main()
{
	fstream file;
	
//	char sysInputFile[] = "{sysFileUrl}";
	char sysInputFile[] = "in";
	file.open(sysInputFile);
	string lineBuffer;
	int m;
	int x,y;
	file>>m;
	while(m--){
		s.clear();
		file>>n;	
		for(int i=0;i<n;i++){
			file>>x>>y;
			s.push_back(PT(x,y));
		}
		doi();
		cout<<endl;
	}
	return 0;
}
