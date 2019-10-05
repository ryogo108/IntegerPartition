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

int detect(vector<long long> A){
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
