#include"../IdentityFinder/common.cpp"
#include"../Polynomial/Polynomial.cpp"
const int MAX_N=1005;

vector<vector<long long> >Dp;

void calcDp(int n){
  Dp.resize(n+1,vector<long long>(n+1));
  Dp[1][1]=1;
  for(int i=0;i<=n;i++){
    Dp[0][i]=1;
    Dp[2][i]=0;
  }
  for(int i=1;i<=n;i++){
    if(i==2)continue;
    for(int j=1;j<=n;j++){
      if(i==j && i<=6)Dp[i][j]=Dp[i][j-1]+1;
      else if(j%2==1 && i>=j && j>=6)Dp[i][j]=Dp[i][j-1]+Dp[i-j][j-6];
      else if(j%2==0 && i>=j && j>=7)Dp[i][j]=Dp[i][j-1]+Dp[i-j][j-7];
      else Dp[i][j]=Dp[i][j-1];
    }
  }
  vector<long long>v(n+1);
  for(int i=0;i<=n;i++){
    v[i]=Dp[i][i];
  }
  print_vector(v);
  vector<long long>A=Factor(v);
  printPeriodOfSeq(A);
}

vector<part> partitions;

bool checkConditions(Par & p){
	bool f=true;
	for(int i=0;i<p.size();i++){
		if(p[i]==0)break;
    f=f&&(p[i]!=2);
		if(p[i+1]!=0){
      f=f&&(p[i]-p[i+1]>=6);
      if(p[i]-p[i+1]==6)f=f&&(p[i]%2==1);
    }
	}
	return f;
}

void check_qdiff(const Polynomial & p){
	const int order=2;
  Polynomial A(7,vector<long long>(p[0].size(),0));
  for(int i=0;i<=6;i++){
    if(i==2)continue;
    A[i][i]=1;
  }
  Polynomial C=Polynomial({{0},{0,1}})*Polynomial({{1},{0},{0,1}})*Polynomial({{1},{1},{0},{0},{0},{0,0,1},{0},{0},{0,0,0,0,1},{0,0,0,0,1},{0},{0},{0,0,0,0,0,0,1}});
  Polynomial f=Polynomial({{1,-1}})*p;
  Polynomial g=f-A;
  Polynomial fInv=xInv(f);
  Polynomial pInv=xInv(p);
	vector<Polynomial>coefs(order+1);
	vector<Polynomial>shifted(order+1);
	coefs[0]={{2},{0,-2}};
	coefs[1]={{0},{0},{0},{0},{0},{0},{0,0,0,0,0,0,-1},{0,0,0,0,0,0,0,-1}};
	coefs[2]={{0},{0},{0},{0},{0},{0},{0,0,0,0,0,0,1},{0,0,0,0,0,0,0,-1}};
  shifted[0]=f-A;
  shifted[1]=qShift(f,1);
  shifted[2]=qShift(fInv,1);
	Polynomial diff;
	/*for(int i=0;i<=order;i++){
		diff=diff+coefs[i]*shifted[i];
	}*/
  diff=Polynomial({{1},{0,-1}})*Polynomial({{1},{0},{0,1}})*g-Polynomial({{0},{0},{0},{0},{0},{0},{0,0,0,0,0,0,1}})*(Polynomial({{1},{0},{0},{0,0,1}})*qShift(g,1)+C);
	cout<<"q-diff:"<<endl;
/*	for(int i=0;i<=order;i++){
		print_Polynomial(coefs[i]);
		cout<<"* ";
		cout<<"term["<<i<<"]"<<endl;
	}
	cout<<"= ";*/
	print_Polynomial(diff);
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  //generatePartition(n,partitions);
	//Polynomial p=countFinePartitions(n,partitions,checkConditions);
  calcDp(n);
  Polynomial p=Dp;
	check_qdiff(p);
}

