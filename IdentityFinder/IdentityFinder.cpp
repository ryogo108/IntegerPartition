#include "common.cpp"

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
  bool f = (k>=1&&dist>=1&&diff>=1&&A>=1&&C<D&&D>=2);
  if(!f)return false;
  f=f&&(B>=diff*(A/dist));
  return f;
}

int generatePartition(int n,int tail,int sum,Par prev,vector<int> & params){
  if(sum!=0)prev.push_back(tail);
  Par now(prev);
  if(n<sum || !checkConditions(now,params))return 0;
  if(n==sum){
    //print_vector(now);
    return 1;
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


void enumPartition(int n,vector<int> & params){
  vector<long long> B;
  for(int i=0;i<=n;i++)B.push_back(countPartition(i,params));
  bool f=false;
  for(int i=0;i<B.size();i++)if(B[i]!=0)f=true;
  if(!f)return;
  vector<long long> A(Factor(B));
  int l=detect(A);
  if(l>2){
    cout<<"params:(sp,dist,diff,A,B,C,D):";print_vector(params);
    cout<<"n="<<l<<" ";
    //print_vector(B);
    vector<long long>v(A.begin()+1,A.begin()+l+1);
    print_vector(v); 
  }
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
  identityFinder(n,4,7,params);
}
