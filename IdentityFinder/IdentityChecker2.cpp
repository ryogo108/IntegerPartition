#include"common.cpp"
vector<part> partitions;
int k=3;
bool checkConditions(Par & p){	
	const int D=2*k;
	const int ap=(1<<1)|(1<<((1+k)%D))|(1<<((2+k)%D));
	const int dist=1;
	const int diff=D;
	const int residue=(1<<1)|(1<<((1+k)%D));
	if(D==0 || diff==0)return true;
	bool f=true;
	for(int i=0;i<p.size();i++){
		if(p[i]==0)break;
		else{
			f=f&&((ap>>((p[i]%D))&1)==1);
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
	return f;
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
	k=atoi(argv[2]);
  generatePartition(n,partitions);
	vector<long long>v(countPartitions(n,partitions,checkConditions));
	print_vector(v);
	vector<long long>A(Factor(v));
	print_vector(A);
	printPeriodOfSeq(A);
}
