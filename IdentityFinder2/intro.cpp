#include<vector>
#include<iostream>

using namespace std;
int max(int a,int b){
  return a>b?a:b;
}

template<class T>void printVector(vector<T> & vec){
  for(int i=0;i<vec.size();i++){
    if(i>0)cout<<" ";
    cout<<vec[i];
  }
  cout<<endl;
}
vector<long long> Factor(vector<long long> &  B){//今はここが律速
  //Eulerのアルゴリズム
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
  //列Aが周期的かどうか調べその周期を返す
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
  //列Seqが周期的なときその1周期分の列を表示する
  int l=detect(Seq);
	vector<long long>v;
	for(int i=1;i<=l;i++){
		if(Seq[i]!=0)v.push_back(Seq[i]*(i));
	}
  if(v.empty())return;
  cout<<"(mod  "<<l<<" ): ";
  printVector(v);
}
void checkSeq(vector<long long>& Seq){
  printVector(Seq);
  vector<long long>B=Factor(Seq);
  printPeriodOfSeq(B);
}

const int MAX_N=30;
const int MOD=6;
long long dp[MAX_N+5][MAX_N+5][MOD];
vector<long long>A(MAX_N+1);
int main(){
  dp[0][0][0]=1;
  int data[MOD][MOD]={
    {12,11,10,9,8,7},
    {7,12,11,10,9,8},
    {8,7,6,11,10,9},
    {9,8,7,12,11,10},
    {10,9,8,7,6,11},
    {11,10,9,8,7,6}
  };
  for(int i=0;i<MAX_N+1;i++){
    for(int j=1;j<MAX_N+1;j++){
      for(int k=0;k<MOD;k++){
        dp[i][j][k]=dp[i][j-1][k];
        if(i>=j && j%MOD==k){
          for(int r=0;r<MOD;r++){
              if(j-data[k][k]>=-1*MOD)dp[i][j][k]+=dp[i-j][max(j-data[k][r],0)][r];
            }
        }
      }
    }
    for(int r=0;r<MOD;r++)A[i]+=dp[i][i][r];
    cout<<i<<" : "<<A[i]<<endl;
  }
  checkSeq(A);
}
