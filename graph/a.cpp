#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<set>
#include <stack>
#include <cstring>
using namespace std;

const char ED	= '$';//'\003';
const char OUT[][5]	= {"NO","YES"};
template<typename T>
class Set
{
	public:
		void clear(){
			_set.clear();
		}
		bool empty(){
			return _set.empty();
		}
		void insert(T item){
			_set.insert(item);
		}
		Set operator*(const Set<T>& st){
			Set nr;
			set_intersection(_set.begin(),_set.end(),
					st._set.begin(),st._set.end(),
					inserter(nr._set,nr._set.begin()));

			return nr;
		}
		friend ostream& operator<<(ostream& os,const Set<T>& st){
			os<<"Set:";
			for(typename set<T>::iterator it=st._set.begin();it!=st._set.end();it++){
				os<<*it<<",";
			}
			os<<":"<<endl;
		}
	private:
		set<T> _set; 
};
#define C 129
template<typename TType>
struct Trie;
typedef Trie<char> SuffixTree;
template<typename TType>
struct Trie
{
	Trie(){
		data='0';
		parent=NULL;
		ct=0;
		memset(childs,0,C*sizeof(Trie*));
	}

	virtual ~Trie(){
    	clear();
	}

	void clear(){
//    printf("Clr:%c,ct=%d\n",data,ct);
		if(ct>0)
			for(int i=0;i<C;i++)
				if(childs[i]){
					//printf("[%c]mait:%c\n",data,i);                
					delete childs[i];
					childs[i]=NULL;
				}
		ct=0;
//        cout<<"DLr:"<<data<<endl;		
	}

	TType data;
	Trie* childs[C];
	Trie* parent;
	int ct;

	Trie* match(const char* str)
	{
		//        printf("dat[%c],ch[%d]=%d\n",data,*str,childs[*str]);
		if(!*str)
			return this;
		else{
			if(childs[*str]==NULL)
				return NULL;
			else
				return childs[*str]->match(str+1);
		}
		printf("Mend!\n");
	}

	void insertPfx(const TType* data,int len){
		for(int i=0;i<len;i++){
			insert(data+i);
		}
	}

	Trie* insert(const TType* data){
		Trie* p;
		Trie* rt;
//printf("childs[%c]=%d\n",*data,childs[*data]);
		if(*data){
			if(childs[*data]!=NULL){
				p=childs[*data];
			}else{
				p = new Trie();
				p->parent=this;
				p->data=*data;
				childs[*data]=p;
				ct++;
//printf("ins!\n");			
			}
			//            printf("x+1 %c %d\n",*(data),*(data));		
			//            printf ( "this\n" );
			rt=p->insert(data+1);
			//            printf ( "Got: %c\n",rt->data );
		}else{
			//            printf("ret!");
			rt=this;
		}
		return rt;
	}

	void BackPrint(){
		Trie* p=this;
		while(p->parent){
			printf("%c ->",p->data);	
			p=p->parent;
		};
		printf ("]\n");
	}

	void btr(int i,Set<int>& se){
		//        this->BackPrint();
		stack<SuffixTree*> stk;
		stack<int> sti;
		stk.push(this);
		sti.push(0);
		int va;
		while(!stk.empty()){
			SuffixTree* st=stk.top();stk.pop();
			va=sti.top();sti.pop();
//    cout<<"d->"<<st->data<<endl;			
			if(st->ct==0){
				se.insert(va);
			}else{
				//cout<<"CH="<<it->first<<endl;
				//getchar();
				int ck=st->ct;
				for(int i=0;i<C;i++)
					if(st->childs[i]){
						stk.push(st->childs[i]);
						sti.push(va+1);
						if(--ck==0)break;
					}
			}
		}
	}
};



#define N 1004
#define NI 15
SuffixTree sk[N];
int n=0,m,ni,mi;
char buf[N];
char r[NI][NI];


Set<int> Tget(SuffixTree& st,const char* dat)
{
	Set<int> rt;
	SuffixTree* s1 = st.match(dat);
	if(s1!=NULL){
		s1->btr(0,rt);
	}
	return rt;
}

int measure()
{
	Set<int> sa,sb;
	for(int i=0;i<n-ni+1;i++){
		sa.clear();
		sa=Tget(sk[i],r[0]);
		//cout<<sa;		
		if(sa.empty())continue;
		for(int k=1;k<ni;k++){
			sb=Tget(sk[i+k],r[k]);
			//cout<<sb;			
			sa=sa*sb;
			if(sa.empty())break;
		}
		if(!sa.empty())return 1;
	}
	return 0;
}

void Clr(){
	for(int i=0;i<n;i++){
//cout<<"Inclean"<<i<<endl;	
		sk[i].clear();
	}
}

int main()
{
	FILE* file;
	int i,j,k;
	file=fopen("{sysFileUrl}","r");
	Clr();
	while(true){
		fscanf(file,"%d%d%d",&n,&m,&k);
//        printf("%d,%d,%d\n",n,m,k);
		if(n==0 && m==0 && k==0)break;
		for(i=0;i<n;i++){
			fscanf(file,"%s",buf);
			buf[m]=ED;
			buf[m+1]='\0';
			sk[i].insertPfx(buf,m+1);
//            Set<int> f=Tget(sk[i],"A");
//            cout<<f<<endl;
//            return 0;
		}
		for(i=0;i<k;i++){
			fscanf(file,"%d%d",&ni,&mi);
			//printf("nimi%d,%d",ni,mi);			
			for(j=0;j<ni;j++){
				fscanf(file,"%s",r[j]);
			}
			printf("%s\n",OUT[measure()]);
		}
		Clr();
//        break;
	}

	fclose(file);
	return 0;
}
