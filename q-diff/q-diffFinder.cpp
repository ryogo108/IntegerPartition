#include"../IdentityFinder/common.cpp"
#include"../Polynomial/Polynomial.cpp"

vector<part> partitions;

bool checkConditions(Par & p){
	bool f=true;
	for(int i=0;i<p.size();i++){
		if(p[i]==0)break;
		if(p[i+1]!=0)f=f&&(p[i]-p[i+1]>=2);
	}
	return f;
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  generatePartition(n,partitions);
	Polynomial p=countFinePartitions(n,partitions,checkConditions);
	Polynomial xq={{0},{0,1}};
	Polynomial diff=p-qShift(p,1)-xq*qShift(p,2);
	print_Polynomial(diff);
}

