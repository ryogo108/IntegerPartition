#include"../IdentityFinder/common.cpp"
#include"../Polynomial/Polynomial.cpp"
const int MAX_N=1005;

vector<part> partitions;

bool checkConditions(Par & p){
	bool f=true;
	for(int i=0;i<p.size();i++){
		if(p[i]==0)break;
		if(p[i+1]!=0){
      if(p[i]%3==0)f=f&&(p[i]-p[i+1]==2 || p[i]-p[i+1]>=4);
      if(p[i]%3==1)f=f&&(p[i]-p[i+1]==0 || p[i]-p[i+1]>=2);
      if(p[i]%3==2)f=f&&(p[i]-p[i+1]==0 || p[i]-p[i+1]>=2);
    //  f=f&&(p[i]-p[i+1]!=1);
    }
	}
	return f;
}

void check_qdiff(const Polynomial & p){
	const int order=6;
	vector<Polynomial>coefs(order+1);
	vector<Polynomial>shifted(order+1);
  /*coefs[0]=Polynomial({{1},{0,-1}});
  coefs[1]=Polynomial({{-1},{0,1}});
  coefs[2]=Polynomial({{0},{0,-1}});*/
  coefs[0]=Polynomial({{-1},{0,1}});
  coefs[1]=Polynomial({{0},{0,-1},{0,1}});
  coefs[2]=Polynomial({{0},{0,1},{0,-1}});
  coefs[3]=Polynomial({{1},{0},{0,1}});
  coefs[4]=Polynomial({{0},{0},{0},{0,1}});
  coefs[5]=Polynomial({{0},{0},{0},{0,-1}});
  coefs[6]=Polynomial({{0},{0},{0},{0,1}});
  shifted[0]=p;
  shifted[1]=qShift(p,1);
  shifted[2]=qShift(p,2); 
  shifted[3]=qShift(p,3); 
  shifted[4]=qShift(p,4); 
  shifted[5]=qShift(p,5); 
  shifted[6]=qShift(p,6); 
/*  shifted[0]=p;
  shifted[1]=qShift(p,1);
  shifted[2]=qShift(p,2); */
  
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
  Polynomial p=countRefinedPartitions(n,partitions,checkConditions);
	check_qdiff(p);
}

