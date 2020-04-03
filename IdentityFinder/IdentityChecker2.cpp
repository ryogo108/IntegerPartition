#include"common.cpp"
vector<part> partitions;
int k=3;
bool checkConditions(Par & p){	
  bool f=true;
  for(int i=0;i<p.size();i++){
    if(p[i]==0)break;
    if(p[i+1]!=0){
      f=f&&(p[i]-p[i+1]>=1);
    }
  }
  return f;
}
int checkNewConditions(Par & p){	
  bool f=true;
  int cnt=1;
  for(int i=0;i<p.size();i++){
    if(p[i]==0)break;
    f=f&&(p[i]!=2);
    if(p[i]%8==0)cnt*=2;
    if(p[i]>4 && p[i]%8==4)cnt*=2;
    if(p[i]==9 && p[i+1]==0)cnt+=1;
    if(p[i]==16 && p[i+1]==0)cnt+=1;
    if(p[i]==24 && p[i+1]==0)cnt+=2;
    if(p[i]==24 && p[i+1]==1)cnt+=1;
    if(p[i+1]!=0){
      f=f&&(p[i]-p[i+1]>=8);
      if(p[i]%2==0)f=f&&(p[i]-p[i+1]>8);
    }
  }
  if(f)return cnt;
  else return 0;
}
int checkNewConditionsOdd(Par & p){	
  bool f=true;
  int cnt=1;
  for(int i=0;i<p.size();i++){
    if(p[i]==0)break;
    f=f&&(p[i]%2==1);
    if(p[i+1]!=0){
      f=f&&(p[i]-p[i+1]>=1);
    }
  }
  if(f)return cnt;
  else return 0;
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  generatePartition(n,partitions);
	vector<long long>v(countColoredPartitions(n,partitions,checkNewConditions));
	printVector(v);
	vector<long long>A(Factor(v));
	printVector(A);
	printPeriodOfSeq(A);
}
