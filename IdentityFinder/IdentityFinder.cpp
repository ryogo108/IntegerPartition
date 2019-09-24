#include<iostream>
#include<vector>
using namespace std;

typedef vector<long long> Par;

template<class T>void print_vector(vector<T> vec){
  for(int i=0;i<vec.size();i++){
    if(i>0)cout<<" ";
    cout<<vec[i];
  }
  cout<<endl;
}


bool diffAtDist(Par & p,int dist,int diff){
  if(p.size()<dist)return true;
  for(int i=0;i<p.size()-dist;i++){
    if(p[i]-p[i+dist]<diff)return false;
  }
  return true; 
}
bool congruenceAtDist(Par & p,int A,int B,int C,int D){
  // diff of lamda_j and lamda_{j+A} is less than or equal to B only if sum from lamda_j to lamda_{j+A} is congruence to C (mod D)
  if(p.size()<A)return true;
  for(int i=0;i<p.size()-A;i++){
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
  return p[p.size()-1]>=n;
}

bool I1(Par p){
  return diffAtDist(p,2,3)&&congruenceAtDist(p,1,1,0,3)&&smallestPart(p,1);
}
bool I2(Par p){
  return diffAtDist(p,2,3)&&congruenceAtDist(p,1,1,0,3)&&smallestPart(p,2);
}
bool I3(Par p){
  return diffAtDist(p,2,3)&&congruenceAtDist(p,1,1,0,3)&&smallestPart(p,3);
}
bool I4(Par p){
  return diffAtDist(p,2,3)&&congruenceAtDist(p,1,1,2,3)&&smallestPart(p,2);
}
bool I5(Par p){
  Par tmpp(p);
  if(!tmpp.empty())tmpp.pop_back();
  return diffAtDist(p,3,3)&&congruenceAtDist(p,2,1,1,3)&&smallestPart(tmpp,2);
}
bool I6(Par p){
  Par tmpp(p);
  if(!tmpp.empty())tmpp.pop_back();
  return diffAtDist(p,3,3)&&congruenceAtDist(p,2,1,2,3)&&smallestPart(tmpp,3)&&smallestPart(p,2);
}

bool euler(Par p){
  return diffAtDist(p,1,1);
}
bool RogersRamanujan(Par p){
  return diffAtDist(p,1,2);
}

bool checkConditions(Par & p,vector<int> & params){
  if(params.size()<7)return false;
  int k=params[0];
  int dist=params[1];
  int diff=params[2];
  int A=params[3];
  int B=params[4];
  int C=params[5];
  int D=params[6];
  if(dist<1||A<1||C>=D||D<1)return false;
  return smallestPart(p,k)&&diffAtDist(p,dist,diff)&&congruenceAtDist(p,A,B,C,D);
}
bool checkParams(vector<int> & params){
  if(params.size()<7)return false;
  int k=params[0];
  int dist=params[1];
  int diff=params[2];
  int A=params[3];
  int B=params[4];
  int C=params[5];
  int D=params[6];
  bool f = (k>=1&&dist>=1&&A>=1&&C<D&&D>=1);
  
  return f;
}

int generatePartition(int n,int tail,int sum,Par prev,vector<int> & params){
  if(sum!=0)prev.push_back(tail);
  Par now(prev);
  if(n<sum)return 0;
  if(n==sum){
    if(checkConditions(now,params)){
     // print_vector(now);
      return 1;
    }
    return 0;
  }
  int re=0;
  for(int i=tail;i>=1;i--){
     re+=generatePartition(n,i,sum+i,now,params);
  }
  return re;
}
int countPartition(int n,vector<int> &params){
  Par p;
  return generatePartition(n,n,0,p,params);
}

vector<int> Factor(vector<int> B){
  vector<int> A;
  A.push_back(0);
  for(int i=1;i<B.size();i++){
    int t=i*B[i];
    for(int d=1;d<i;d++){
      if((i%d)==0)t-=d*A[d];
    }
    for(int j=1;j<i;j++){
      int tmp=0;
      for(int d=1;d<=j;d++){
       if((j%d)==0)tmp+=d*A[d];
      }
      t-=tmp*B[i-j];
    }
    A.push_back(t/i);
  }
  return A;
}

void enumPartition(int n,vector<int> & params){
  vector<int> B;
  for(int i=0;i<=n;i++)B.push_back(countPartition(i,params));
  int sum=0;
  for(int i=0;i<B.size();i++)sum+=B[i];
  if(sum==0)return;
  cout<<"params:(sp,dist,diff,A,B,C,D):";print_vector(params);
  print_vector(B);
  print_vector(Factor(B)); 
}
void identityFinder(int n,int param_max,int param_num,vector<int> params){
  if(params.size()==param_num){
    if(checkParams(params))enumPartition(n,params);
    return;
  }
  for(int i=0;i<=param_max;i++){
    vector<int> next(params);
    next.push_back(i);
    identityFinder(n,param_max,param_num,next);
  }
}
int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  vector<int> params;
  identityFinder(n,3,7,params);
}
