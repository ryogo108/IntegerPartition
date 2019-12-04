#include"common.cpp"

vector<part> partitions;

bool checkConditions(Par & p){
	bool f=true;
	for(int i=0;i<p.size();i++){
		if(p[i]==0)break;
		f=f&&(p[i]%2==1);
		if(p[i+1]!=0)f=f&&(p[i]-p[i+1]>=1);
	}
	if(f)print_partition(p);
	return f;
/*	int np=2;
	int dist=1;
	int diff=6;
	int residue=42;
	bool f=true;
	for(int i=0;i<p.size();i++){
		if(p[i]==0)break;
		else{
			for(int j=1;j<=5;j++){
				if((np>>(j-1))&(1))f=f&&(p[i]!=j);
			}
		}
		if(p[i+dist]!=0){
			f=f&&(p[i]-p[i+dist]>=diff);
			if(p[i]-p[i+dist]==diff){
				bool tmp=false;
				for(int j=0;j<=diff;j++){
					if((residue>>(j))&1)tmp=tmp||(p[i]%(diff)==j);
				}
				f=f&&tmp;
			}
		}
	}
	if(f)print_partition(p);
	return f;*/
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
