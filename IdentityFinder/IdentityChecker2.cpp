#include"common.cpp"
vector<part> partitions;
int k=3;

int gcd(int a,int b){
  if(b==0)return a;
  if(b>a)return gcd(b,a);
  return gcd(b,a%b);
}

bool checkConditions(Par & p){	
  bool f=true;
	return f;
}
bool checkConditions1(Par & v){	
  bool f=true;
  int cnt=0;
  for(int i=0;i<v.size();i++){
    if(v[i]==0)break;
    if(i==0){
      cnt++;
      continue;
    }
    if(v[i]==v[i-1]){
      cnt++;
    }
    else cnt=1;
    if(cnt>=k)f=false;
  }
	return f;
}
bool checkConditions2(Par & v){	
  bool f=true;
  for(int i=0;i<v.size();i++){
    if(v[i]==0)break;
    f=f&&(gcd(v[i],k)==1);
  }
	return f;
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
	k=atoi(argv[2]);
  generatePartition(n,partitions);
	vector<long long>v1(countPartitions(n,partitions,checkConditions1));
	vector<long long>v2(countPartitions(n,partitions,checkConditions2));
  print_vector(v1);
  print_vector(v2);
	/*vector<long long>A(Factor(v));
	print_vector(A);
	printPeriodOfSeq(A);*/
}
