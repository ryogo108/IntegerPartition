#include"common.cpp"

vector<part> partitions;

void SearchSp_KR1(int n){
  rep(k,6)rep(A,4)rep(B,9)rep(C,9)rep(D,9){
		int i=1,j=4;
    bool f = (k>=1&&i>=1&&j>=1&&A>=1&&C<D&&D>=2);
    if(!f)continue;
    f=f&&(B>=j*(A/i));
    if(!f)continue;
    vector<int>params={k,i,j,A,B,C,D};
    vector<long long>count=countPartitions(n,partitions,generateConditionsKR1(params));
    vector<long long> A=Factor(count);
    printPeriodOfSeq(A); 
  }
}
void SearchSp_Schur(int n){
	rep(f1,4)rep(f2,4)rep(a,9)rep(b,9)rep(c,9)rep(d,9){
		if(f1 >f2 || a>b || c>d || d<2)continue;
		vector<int>params={f1,f2,a,b,c,d};
		vector<long long>count=countPartitions(n,partitions,generateConditionsSchur(params));
		vector<long long>A=Factor(count);
		printPeriodOfSeq(A);
	}
}
void SearchSp_Original4(int n){
	rep(sp,5)rep(s,5)rep(t,5)rep(x,10)rep(sw,2){
		vector<int>params={sp,s,t,x,sw};
		vector<long long>count=countPartitions(n,partitions,generateConditionOriginal4(params));
		vector<long long>A=Factor(count);
		printPeriodOfSeq(A);
	}
}
void SearchSp_Original5(int n){
	rep(sp,5)rep(dist,4)rep(diff,6)rep(a,9)rep(b,4){
		if(sp==0 || a==0)continue;
		vector<int>params={sp,dist,diff,a,b};
		vector<long long>count=countPartitions(n,partitions,generateConditionOriginal5(params));
		vector<long long>A=Factor(count);
		print_vector(A);
		printPeriodOfSeq(A);
	}
}


int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  generatePartition(n,partitions);
	SearchSp_KR1(n);
}
