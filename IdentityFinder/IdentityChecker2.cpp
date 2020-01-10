#include"common.cpp"
#include<algorithm>
vector<part> partitions;
int k=3;

int gcd(int a,int b){
  if(b==0)return a;
  if(b>a)return gcd(b,a);
  return gcd(b,a%b);
}

Par trans(Par & p){
  Par r(p);
  for(int i=0;i<p.size()-1;i++){
		if(r[i]-r[i+1]==2){
			r[i]+=r[i+1];
			r[i+1]=0;
			i++;
		}
  }	
	sort(r.rbegin(),r.rend());
  return r;
}

bool checkConditions(Par & p){	
  bool f=true;
	return f;
}
bool checkConditions1(Par & v){	
  bool f=true;
	for(int i=0;i<v.size();i++){
		if(v[i]==0)break;
		f=f&&(v[i]%k==1);
		if(v[i+1]!=0)f=f&&(v[i]-v[i+1]>=1);
	}
	return f;
}
bool checkConditions2(Par & v){	
  bool f=true;
  for(int i=0;i<v.size();i++){
    if(v[i]==0)break;
    f=f&&(v[i]%(2*k)==1 || v[i]%(2*k)==k+1 || v[i]%(2*k)==(k+2)%(2*k));
		if(v[i+1]!=0){
			f=f&&(v[i]-v[i+1]>=(2*k));
			if(v[i]-v[i+1]==2*k)f=f&&(v[i]%k==1);
		}
  }
	return f;
}
bool checkConditions3(Par & v){	
  Par t=trans(v);
  bool f=(checkConditions1(v)&&(!checkConditions2(v)));
  f=f&&(!checkConditions2(t));
  f=f&&(v[4]==0);
  return f;
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
	k=atoi(argv[2]);
  generatePartition(n,partitions);
/*	cout<<"Condition1:"<<endl;
	enumPartitions(n,partitions,checkConditions1);
	cout<<"Condition2:"<<endl;
	enumPartitions(n,partitions,checkConditions2);*/
  cout<<"Condition1-Condition2 and trans:"<<endl;
  enumPartitions(n,partitions,checkConditions3);
	/*vector<long long>A(Factor(v));
	print_vector(A);
	printPeriodOfSeq(A);*/
}
