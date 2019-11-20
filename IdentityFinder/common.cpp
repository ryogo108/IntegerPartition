#include<iostream>
#include<vector>
#include<cstdint>
#include<functional>
using namespace std;

#define rep(i, n) for(int i = 0; i < (int)(n); i++)


typedef unsigned short part; //size of max part in all partitions.
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
		cout<<p[i];
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


bool diffAtDist(Par & p,int dist,int diff){
  if(p.size()<dist)return true;
  for(int i=0;i<p.size()-dist;i++){
    if(p[i+dist]==0)break;
    if(p[i]-p[i+dist]<diff)return false;
  }
  return true; 
}
bool congruenceAtDist(Par & p,int A,int B,int C,int D){
  // diff of lamda_j and lamda_{j+A} is less than or equal to B only if sum from lamda_j to lamda_{j+A} is congruence to C (mod D)
  if(p.size()<A || D==0)return true;
  for(int i=0;i<p.size()-A;i++){
    if(p[i+A]==0)break;
    if(p[i]-p[i+A]<=B){
      int sum=0;
      for(int j=0;j<=A;j++)sum+=p[i+j];
      if(sum%D!=C)return false;
    }
  }
  return true;
}
bool smallestPart(Par & p,int n){
  if(p.empty())return true;
  for(int i=p.size()-1;i>=0;i--){
    if(p[i]==0)continue;
    return p[i]>=n;
  }
  return p[0]>=n;
}
function<bool(Par &)> generateConditionsKR1(vector<int> & params){
  cout<<"Condition:";
  print_vector(params);
  return [&params](Par & p)->bool{
    bool f=diffAtDist(p,params[0],params[1])&&smallestPart(p,params[2])&&congruenceAtDist(p,params[3],params[4],params[5],params[6]);
    return f;
  };
}


function<bool(Par &)>generateConditionsSchur(vector<int> & params){
	cout<<"Condition(schur):";
	print_vector(params);
	return [&params](Par & p)->bool{
		bool f=true;
		int a=params[0];
		if(a==0)return true;
		for(int i=0;i<p.size();i++){
			if(p[i+1]==0)break;
			if(p[i]%a==0)f=f&&((p[i]-p[i+1])>a);
			else f=f&&((p[i]-p[i+1])>=a);
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
  cout<<"mod : "<<l<<endl;
  print_vector(v);
}
