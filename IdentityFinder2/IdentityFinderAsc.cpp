#include<vector>
#include"Matrix.cpp"
#include<iostream>
#include<set>

using namespace std;
int max(int a,int b){
  return a>b?a:b;
}

template<class T>void printVector(vector<T> & vec){ for(int i=0;i<vec.size();i++){ if(i>0)cout<<" ";
    cout<<vec[i];
  }
  cout<<endl;
}
template<class T>void printSet(set<T> & s){
  for(set<int>::iterator itr=s.begin();itr!=s.end();itr++){
    if(itr!=s.begin())cout<<" ";
    cout<<*(itr);
  }
  cout<<endl;
}
vector<long long> Factor(vector<long long> &  B){
  //Eulerのアルゴリズム
  vector<long long> A(B.size(),0);
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
    A[i]=(t/i);
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
 // printVector(Seq);
  vector<long long>B=Factor(Seq);
  if(printPeriodOfSeq(B))return true;
  else return false;
}

const int MAX_N=30;
const int MAX_MOD=5;
long long dp[MAX_N+5][MAX_N+5][MAX_MOD+1];
vector<long long>A(MAX_N+1);

void countPartition(Mat<int> ker,Mat<int> shift, set<int> forbidden=set<int>()){
  int mod=ker.size();
  Mat<int>data=mod*ker+shift;
  //printMatrix(data);
  fill(A.begin(),A.end(),0);
  for(int i=0;i<MAX_N+5;i++)for(int j=0;j<MAX_N+5;j++)for(int k=0;k<MAX_MOD+1;k++)dp[i][j][k]=0;
  dp[0][0][0]=1;
  for(int i=0;i<MAX_N+1;i++){
    for(int j=1;j<MAX_N+1;j++){
      for(int k=0;k<mod;k++){
        dp[i][j][k]=dp[i][j-1][k];
        if(i>=j && j%mod==k){
          for(int r=0;r<mod;r++){
              if(forbidden.find(j)==forbidden.end())dp[i][j][k]+=dp[i-j][max(j-data[k][r],0)][r];
            }
        }
      }
    }
    for(int r=0;r<mod;r++)A[i]+=dp[i][i][r];
    //cout<<i<<" : "<<A[i]<<endl;
  }
  if(checkSeq(A)){
    //cout<<"dil : "<<mod<<endl;
    cout<<"forbidden : ";
    printSet(forbidden);
    cout<<"ker : "<<endl;
    printMatrix(ker);
    /*cout<<"shift : "<<endl;
    printMatrix(shift);*/
  }
}
Mat<int> shift;
void dfs_forbidden(Mat<int> mat,int cnt,int max,set<int> now){
  if(cnt==max){
    countPartition(mat,shift,now);
  }
  else{
    dfs_forbidden(mat,cnt+1,max,now);
    now.insert(cnt);
    dfs_forbidden(mat,cnt+1,max,now);
  }
}
void dfs(int size,int max,int depth,Mat<int> now){
  if(depth==size*size){
    //countPartition(now,shift);
    dfs_forbidden(now,1,5,set<int>());
  }
  else{
    for(int i=0;i<=max;i++){
      if(4*i+shift[depth/size][depth%size]<0)continue;
      now[depth/size][depth%size]=i;
      dfs(size,max,depth+1,now);
    }
  }
}
void search2(int size,int max,int depth,Mat<int> now){
  if(depth==size*size){
    dfs_forbidden(now,1,5,set<int>());
    //countPartition(now,shift,forbidden);
  }
  else{
    int r=depth/size;
    int c=depth%size;
    if(r<c){
      now[r][c]=2;
      search2(size,max,depth+1,now);
    }
    else if(r>c){
      now[r][c]=1;
      search2(size,max,depth+1,now);
    }
    else{
      for(int i=1;i<=max;i++){
        now[r][c]=i;
        search2(size,max,depth+1,now);
      }
    }
  }
}
int main(int argc, char *argv[]){
  int s=atoi(argv[1]),m=atoi(argv[2]);
  shift.resize(s);
  for(int i=0;i<s;i++){
    shift[i].resize(s);
    for(int j=0;j<s;j++){
      shift[i][j]=i-j;
    }
  }
  Mat<int> now(s,vector<int>(s,0));
  dfs(s,m,0,now);
}
