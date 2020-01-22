#include"common.cpp"
vector<part> partitions;
bool checkConditions(Par & p){	
	const int D=15;
	bool f=true;
	for(int i=0;i<p.size();i++){
		if(p[i]==0)break;
		else{
			f=f&&(p[i]!=2 && p[i]!=3 && p[i]!=4 && p[i]!=5 && (p[i]%5==1 || p[i]%5==2));
		}
		if(p[i+1]!=0){
			f=f&&(p[i]-p[i+1]>=D);
			if(p[i]%5==2){
        f=f&&(p[i]-p[i+1]>D);
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
