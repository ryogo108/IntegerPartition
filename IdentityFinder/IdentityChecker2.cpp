#include"common.cpp"

vector<part> partitions;

bool checkConditions(Par & p){
	bool f=true;
	for(int i=0;i<p.size();i++){
		if(p[i]==0)break;
		else{
			f=f&&(p[i]>=3);
		}
		if(p[i+5]!=0){
			f=f&&(p[i]-p[i+5]>=4);
		}
		if(p[i+2]!=0){
			if(p[i]-p[i+2]<=0)f=f&&((p[i]+p[i+1]+p[i+2])%4==0);
		}
		if(p[i+1]!=0){
			if(p[i]-p[i+1]<=0)f=f&&((p[i]+p[i+1])%5==4);
		}
	}
	return f;
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  generatePartition(n,partitions);
	vector<long long>v(countPartitions(n,partitions,checkConditions));
	print_vector(v);
	vector<long long>A(Factor(v));
	print_vector(A);
	printPeriodOfSeq(A);
}
