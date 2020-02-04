#include"../IdentityFinder/common.cpp"
#include"../Polynomial/Polynomial.cpp"
const int MAX_N=1005;

vector<part> partitions;

bool checkConditions(Par & p){
	bool f=true;
	for(int i=0;i<p.size();i++){
		if(p[i]==0)break;
    f=f&&(p[i]%6==1 || p[i]%6==4 || p[i]%6==5);
		if(p[i+1]!=0){
      f=f&&(p[i]-p[i+1]>=6);
      if(p[i]-p[i+1]==6)f=f&&(p[i]%3==1);
    }
	}
	return f;
}
bool checkConditions2(Par & p){
	bool f=true;
	for(int i=0;i<p.size();i++){
		if(p[i]==0)break;
    f=f&&(p[i]%3==1);
		if(p[i+1]!=0){
      f=f&&(p[i]-p[i+1]>=1);
    }
	}
	return f;
}

void check_qdiff(const Polynomial & p){
	const int order=4;
	vector<Polynomial>coefs(order+1);
	vector<Polynomial>shifted(order+1);
  coefs[0]=qShift(Polynomial({{0,1}}),6)-Polynomial({{1}});
  coefs[1]=-coefs[0];
  coefs[2]=qShift(Polynomial({{0,-1}}),1)*Polynomial({{-1},{0},{0},{0},{1}});
  coefs[3]=qShift(Polynomial({{0,-1}}),5)*(qShift(Polynomial({{0,1}}),2)-Polynomial({{1}}));
  coefs[4]=qShift(Polynomial({{0,-1}}),4)*(qShift(Polynomial({{0,1}}),2)-Polynomial({{1}}));
  shifted[0]=p;
  shifted[1]=qShift(p,2);
  shifted[2]=qShift(p,4);
  shifted[3]=qShift(p,6);
  shifted[4]=qShift(p,8);
  
  
	Polynomial diff;
	for(int i=0;i<=order;i++){
		diff=diff+coefs[i]*shifted[i];
	}
	cout<<"q-diff:"<<endl;
	for(int i=0;i<=order;i++){
		print_Polynomial(coefs[i]);
		cout<<"* ";
		cout<<"term["<<i<<"]"<<endl;
	}
	cout<<"= ";
	print_Polynomial(diff);
}
void test(Polynomial & p1,Polynomial & p2){
  Polynomial diff=p1-p2;
  print_Polynomial(diff);
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  generatePartition(n,partitions);
	Polynomial p=countRefinedPartitions2(n,partitions,checkConditions);
  Polynomial q=countRefinedPartitions(n,partitions,checkConditions2);
	//check_qdiff(p);
  Polynomial r=p-q;
  print_Polynomial(p);
  print_Polynomial(q);
  cout<<"p-q="<<endl;
  print_Polynomial(r);
}

