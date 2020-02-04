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

void seek_qdiff(const Polynomial & p,const int order){
	vector<Polynomial>coefs(order+1);
	vector<Polynomial>shifted(order+1);
	for(int i=0;i<=order;i++){
		shifted[i]=qShift(p,i);
	}
	coefs[0]={{1}};
	coefs[1]={{-1}};
	coefs[2]={{0},{0,-1}};
	Polynomial diff;
	for(int i=0;i<=order;i++){
		diff=diff+coefs[i]*shifted[i];
	}
	cout<<"q-diff:"<<endl;
	for(int i=0;i<=order;i++){
		print_Polynomial(coefs[i]);
		cout<<"* ";
		cout<<"f(xq^"<<i<<")"<<endl;
	}
	cout<<"= ";
	print_Polynomial(diff);
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  generatePartition(n,partitions);
	Polynomial p=countRefinedPartitions(n,partitions,checkConditions);
	seek_qdiff(p,2);
}

