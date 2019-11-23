#include<iostream>
#include<vector>
#include<cstdint>
#include<functional>
#include<queue>
#include"countPartition.cpp"
using namespace std;

#define rep(i, n) for(int i = 0; i < (int)(n); i++)

const int PARTITION_LENGTH=100;

typedef uint_fast8_t part; //size of max part in all partitions.
typedef vector<part> Par;

part min(part l,part r){
  if(r>l)return l;
  else return r;
}

template<class T>void print_vector(vector<T> & vec){
  for(int i=0;i<vec.size();i++){
    if(i>0)cout<<" ";
    cout<<vec[i];
  }
  cout<<endl;
}
void print_partition(Par & p){
	for(int i=0;i<p.size();i++){
		if(i>0 && p[i]==0)break;
		if(i>0)cout<<" ";
		cout<<(short)p[i];
	}
	cout<<endl;
}
template<class T> T sum_vector(vector<T> & vec){
  T re=T(0);
  for(int i=0;i<vec.size();i++){
    re+=vec[i];
  }
  return re;
}
long long sizeOfPartition(int n){ //partition を一列に列挙するのに必要な容量
  long long sum=0;
  for(int i=0;i<=n;i++){
    sum+=numOfPartition(i)*(PARTITION_LENGTH);
  }
  return sum; 
}
void generatePartition(int n,vector<part> & partitions){
  partitions.resize(sizeOfPartition(n));
  for(int i=1;i<=n;i++){
    long long head=sizeOfPartition(i-1);
    long long cnt=0;
    queue<vector<part> > que;
    for(int j=i;j>=1;j--)que.push(vector<part>(1,j));
    while(!que.empty()){
      vector<part> v=que.front();
      que.pop();
      int sum=sum_vector(v);
      if(sum==i){
        copy(v.begin(),v.end(),partitions.begin()+head+cnt*PARTITION_LENGTH);
        cnt++;
        //print_vector(v);
      }
      else{
        for(int k=min(v.back(),i-sum);k>=1;k--){ 
          vector<part> v_new(v);
          v_new.push_back(k);
          que.push(v_new);
        }
      }
    }
    cout<<i<<" : "<<cnt<<endl;
  }
}

vector<long long>countPartitions(int n,vector<part> & ps,function<bool(Par &)>f){ 
  vector<long long>re;
  long long now=0;
  for(int l=0;l<=n;l++){
    long long cap=sizeOfPartition(l);
    long long cnt=0;
    for(;now<cap;now+=PARTITION_LENGTH){
      vector<part>v;
      v.assign(ps.begin()+now,ps.begin()+now+PARTITION_LENGTH);
      if(f(v))cnt++;
    }
    re.push_back(cnt);
  }
  return re;
}

vector<long long> Factor(vector<long long> &  B){
  vector<long long> A;
  A.push_back(0);
  for(int i=1;i<B.size();i++){
    long long t=i*B[i];
    for(int d=1;d<i;d++){
      if((i%d)==0)t-=d*A[d];
    }
    for(int j=1;j<i;j++){
      long long tmp=0;
      for(int d=1;d<=j;d++){
       if((j%d)==0)tmp+=d*A[d];
      }
      t-=tmp*B[i-j];
    }
    A.push_back(t/i);
  }
  return A;
}

int detect(vector<long long> & A){
  int n=A.size();
  for(int i=1;i<=n/2;i++){
    bool f=true;
    for(int j=1;j<n;j++){
      if(A[j]!=A[j%i==0?i:j%i]){
        f=false;
        break;
      }
    }
    if(f)return i;
  }
  return 0;
}
void printPeriodOfSeq(vector<long long> & Seq){
  int l=detect(Seq);
	vector<long long>v;
	for(int i=0;i<l;i++){
		if(Seq[i]!=0)v.push_back(Seq[i]*(i));
	}
  if(v.empty())return;
  cout<<"(mod  "<<l<<" ): ";
  print_vector(v);
}


///Condiions

function<bool(Par &)> generateConditionsKR1(vector<int> & params){
  cout<<"Condition(sp,dist,diff,A,B,C,D):";
  print_vector(params);
	const int sp=params[0];
	const int dist=params[1];
	const int diff=params[2];
	const int A=params[3];
	const int B=params[4];
	const int C=params[5];
	const int D=params[6];
  return [=](Par & p)->bool{
		if(D==0)return true;
		bool f=true;
		for(int i=0;i<p.size();i++){
			if(p[i]==0)break;
			else{
				f=f&&(p[i]>=sp);
			}
			if(p[i+dist]!=0){
				f=f&&(p[i]-p[i+dist]>=diff);
			}
			if(p[i+A]!=0){
				if(p[i]-p[i+A]<=B){
					unsigned short sum=0;
					for(int j=0;j<=A;j++)sum+=p[i+j];
					f=f&&(sum%D==C);
				}
			}
		}
		return f;
  };
}


function<bool(Par &)>generateConditionsSchur(vector<int> & params){
	cout<<"Condition(schur)(f1,f2,a,b,c,d):";
	print_vector(params);
	return [&params](Par & p)->bool{
		bool f=true;
		int f1=params[0];
		int f2=params[1];
		int a=params[2];
		int b=params[3];
		int c=params[4];
		int d=params[5];
		if(d==0)return true;
		for(int i=0;i<p.size();i++){
			if(p[i]==0)break;
			f=f&&(p[i]!=f1)&&(p[i]!=f2);
			if(p[i+1]!=0){
				if(p[i]%d==c)f=f&&((p[i]-p[i+1])>=b);
				else f=f&&((p[i]-p[i+1])>=a);
			}
		}
		return f;
	};
}
function<bool(Par &)>generateConditionsOriginal1(vector<int> & params){
	cout<<"Condition(Origin1):";
	print_vector(params);
	return [&params](Par & p)->bool{
		bool f=true;
		int k=params[0];
		int a=params[1];
		int b=params[2];
		if(b==0||k==0)return true;
		for(int i=0;i+k<p.size();i++){
			if((p[i]-p[i+k-1])==0)f=f&&((p[i]%b)==a);
			if(p[i+k]==0)break;
			f=f&&((p[i]-p[i+k])>=1);
		}
	//	if(f)print_partition(p);
		return f;
	};
}

function<bool(Par &)>generateConditionOriginal4(vector<int> & params){
	//all product has x two
	cout<<" Condition(sp,s,t,x,sw): ";
	print_vector(params);
	return [&params](Par & p)->bool{
		bool f=true;
		int sp=params[0];
		int s=params[1];
		int t=params[2];
		int x=params[3];
		int sw=params[4];
		int cnt=0;
		for(int i=0;i<p.size();i++){
			if(p[i]==0)break;
			f=f&&(p[i]>=sp);
			if(p[i+s]!=0){
				f=f&&((p[i]-p[i+s])>=t);
			}
			int tmp=p[i];
			while(tmp%2==0){
				tmp/=2;
				cnt++;
			}
		}
		if(sw==0)f=f&&(cnt<=x);
		else f=f&&(cnt>=x);
		return f;
	};
}

function<bool(Par &)>generateConditionOriginal5(vector<int> & params){
	cout<<"Condition(sp,dist,diff,a) :";
	print_vector(params);
	return [&params](Par & p)->bool{
		bool f=true;
		int sp=params[0];
		int dist=params[1];
		int diff=params[2];
		int a=params[3];
		int b=params[4];
		for(int i=0;i<p.size();i++){
			if(p[i]==0 || !f)break;
			f=f&&(p[i]>=sp);
			if(p[i+dist]!=0){
				f=f&&(p[i]-p[i+dist]>=diff);
			if(p[i]%a==0)f=f&&(p[i]-p[i+dist]>=diff+b);
			}
		}	
	//	if(f)print_partition(p);
		return f;
	};
}
