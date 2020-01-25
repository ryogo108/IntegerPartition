#include"common.cpp"
vector<part> partitions;
bool checkConditions(Par & p){	
	const int dist=1;
	const int diff=12;
	bool f=true;
	for(int i=0;i<p.size();i++){
		if(p[i]==0)break;
		else{
			f=f&&(p[i]!=2&&p[i]!=3&&p[i]!=6&&p[i]!=9);
		}
		if(p[i+dist]!=0){
			f=f&&(p[i]-p[i+dist]>=diff);
			if(p[i]-p[i+dist]==diff){
        f=f&&(p[i]%3==1);
			}
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
