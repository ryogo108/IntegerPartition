#include<vector>
#include"Matrix.cpp"
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
bool printPeriodOfSeq(vector<long long> & Seq){
  //列Seqが周期的なときその1周期分の列を表示する
  int l=detect(Seq);
	vector<long long>v;
	for(int i=1;i<=l;i++){
		if(Seq[i]!=0)v.push_back(Seq[i]*(i));
	}
  if(v.empty())return false;
  cout<<"(mod  "<<l<<" ): ";
  printVector(v);
  return true;
}
bool checkSeq(vector<long long>& Seq){
  printVector(Seq);
  vector<long long>B=Factor(Seq);
  if(printPeriodOfSeq(B))return true;
  else return false;
}

const int MAX_N=100;
const int MAX_MOD=20;
long long dp[MAX_N+5][MAX_N+5][MAX_MOD+1];
vector<long long>A(MAX_N+1);

void countPartition(Mat<int> ker,Mat<int> shift){
  int mod=ker.size();
  Mat<int>data=mod*ker+shift;

  printMatrix(data);


  fill(A.begin(),A.end(),0);
  for(int i=0;i<MAX_N+5;i++)for(int j=0;j<MAX_N+5;j++)for(int k=0;k<MAX_MOD+1;k++)dp[i][j][k]=0;
  dp[0][0][0]=1;
  for(int i=0;i<MAX_N+1;i++){
    for(int j=1;j<MAX_N+1;j++){
      for(int k=0;k<mod;k++){
        dp[i][j][k]=dp[i][j-1][k];
        if(i>=j && j%mod==k && j != 2){
          for(int r=0;r<mod;r++){
              dp[i][j][k]+=dp[i-j][max(j-data[k][r],0)][r];
            }
        }
      }
    }
    for(int r=0;r<mod;r++)A[i]+=dp[i][i][r];
    //cout<<i<<" : "<<A[i]<<endl;
  }
  if(checkSeq(A)){
    cout<<"dil : "<<mod<<endl;
    cout<<"ker : "<<endl;
    printMatrix(ker);
    cout<<"shift : "<<endl;
    printMatrix(shift);
  }
}
int main(){

Mat<int> ker,shift;
  ker={
    {1, 1, 2, 2, 2, 2, 2, 2},
    {1, 1, 1, 1, 1, 2, 2, 2},
    {1, 1, 2, 2, 2, 2, 2, 2},
    {1, 1, 1, 1, 1, 1, 2, 2},
    {1, 1, 1, 1, 1, 1, 2, 1},
    {1, 1, 1, 1, 1, 1, 2, 1},
    {1, 1, 1, 1, 1, 1, 2, 1},
    {0, 0, 1, 1, 1, 1, 1, 1},
  };
  shift={
    {0, -1, -2, -3, -4, -5, -6, -7},
    {1, 0, -1, -2, -3, -4, -5, -6},
    {2, 1, 0, -1, -2, -3, -4, -5},
    {3, 2, 1, 0, -1, -2, -3, -4},
    {4, 3, 2, 1, 0, -1, -2, -3},
    {5, 4, 3, 2, 1, 0, -1, -2},
    {6, 5, 4, 3, 2, 1, 0, -1},
    {7, 6, 5, 4, 3, 2, 1, 0},
  };
  countPartition(ker,shift);
}
