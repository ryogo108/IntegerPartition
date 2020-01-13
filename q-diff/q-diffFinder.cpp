#include"../IdentityFinder/common.cpp"
#include"../Polynomial/Polynomial.cpp"
#include<math.h>
vector<part> partitions;

bool checkConditions(Par & p){
	bool f=true;
	for(int i=0;i<p.size();i++){
		if(p[i]==0)break;
		if(p[i+1]!=0)f=f&&(p[i]-p[i+1]>=2);
	}
	return f;
}

Polynomial generateCoefs(int seed){
  Polynomial r(10,vector<long long>(2,0));
  int tmp=seed%8;
  if(tmp%4!=0){
    if(tmp<4){
      r[tmp%4-1][0]=1;
    }
    else r[tmp%4-1][0]-=1;
  }
  tmp=seed/8;
  if(tmp%4>0){
    if((tmp/4)==0)r[tmp%4-1][1]=1;
    else r[tmp%4-1][1]=-1;
  }
  return r;
}

bool check_anih(Polynomial & p){
  const int c=20;
  bool f=false;
  if(p.size()<=c)return false;
  int tmp=c;
  for(int i=0;i<=c;i++){
    if(p[i].size()<=c)return false;
    for(int j=0;j<=c;j++){
      if(p[i][j]!=0)return false;
    }
    f=f||(p[i][c+1]!=0);
  }
  return f;
}
void seek_qdiff(const Polynomial & p,const int order){
	vector<Polynomial>coefs(order+1);
	vector<Polynomial>shifted(order+1);
	for(int i=0;i<=order;i++){
		shifted[i]=qShift(p,i);
	}
  Polynomial result;
  for(int i=1;i<pow(64,order+1);i++){
    Polynomial diff;
    int tmp=i;
    for(int j=0;j<order+1;j++){
      coefs[j]=generateCoefs(tmp%64);
      tmp/=64;
    }
  	for(int i=0;i<=order;i++){
	  	diff=diff+coefs[i]*shifted[i];
	  }
    
    if(check_anih(diff)){ 
      result=diff;
      break;
    }
  }
	cout<<"q-diff:"<<endl;
	for(int i=0;i<=order;i++){
		print_Polynomial(coefs[i]);
		cout<<"* ";
		cout<<"f(xq^"<<i<<")"<<endl;
	}
	cout<<"= ";
	print_Polynomial(result);
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  generatePartition(n,partitions);
	Polynomial p=countFinePartitions(n,partitions,checkConditions);
	seek_qdiff(p,2);
}

