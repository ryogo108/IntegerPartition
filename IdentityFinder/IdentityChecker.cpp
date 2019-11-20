#include"common.cpp"

bool checkConditions(Par & p){
  return diffAtDist(p,2,1)&&smallestPart(p,1)&&congruenceAtDist(p,1,0,0,3);
}
int generatePartition(int n,int tail,int sum,Par prev){
  if(sum!=0)prev.push_back(tail);
  Par now(prev);
  if(n<sum || !checkConditions(now))return 0;
  if(n==sum){
    //print_vector(now);
    return 1;
  }
  int re=0;
  for(int i=tail;i>=1;i--){
     re+=generatePartition(n,i,sum+i,now);
  }
  return re;
}
int countPartition(int n){
  Par p;
  return generatePartition(n,n,0,p);
}

void enumPartition(int n){
  vector<long long> B;
  for(int i=0;i<=n;i++)B.push_back(countPartition(i));
  bool f=false;
  for(int i=0;i<B.size();i++)if(B[i]!=0)f=true;
  if(!f)return;
  vector<long long> A(Factor(B));
  int l=detect(A);
  print_vector(B);
  print_vector(A);
  if(l>2){
    cout<<"n="<<l<<" ";
    vector<long long>v(A.begin()+1,A.begin()+l+1);
    print_vector(v); 
  }
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  enumPartition(n);
}
