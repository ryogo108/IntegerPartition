#include<math.h>
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
void SearchSp_Original6(int n){
  rep(k,6)rep(i,6)rep(j,6)rep(A1,6)rep(B1,6)rep(C1,6)rep(D1,6)rep(A2,6)rep(B2,6)rep(C2,6)rep(D2,6){
    bool f = (k>=1&&i>=1&&j>=1&&A1>=1&&C1<D1&&D1>=2);
		f=f&&(A2>=1&&C2<D2&&D2>=2);
    if(!f)continue;
    f=f&&(B1>=j*(A1/i));
    f=f&&(B2>=j*(A2/i));
    if(!f)continue;
    vector<int>params={k,i,j,A1,B1,C1,D1,A2,B2,C2,D2};
    vector<long long>count=countPartitions(n,partitions,generateConditionsOriginal6(params));
    vector<long long> A=Factor(count);
    printPeriodOfSeq(A); 
  }
}

void SearchSp_GeneralMacMahon(int n){
	rep(sp,5)rep(k,5){
		vector<int>params={sp,k};
		vector<long long>count=countPartitions(n,partitions,generateConditionsGeneralMacMahon(params));
		vector<long long>A=Factor(count);
		printPeriodOfSeq(A);
	}
}
void SearchSp_Original6_1(int n){
  rep(k,6)rep(A1,9)rep(B1,9)rep(C1,9)rep(D1,9){
		int i=5,j=4;
    bool f = (k>=1&&i>=1&&j>=1&&A1>=1&&C1<D1&&D1>=2);
    if(!f)continue;
    f=f&&(B1>=j*(A1/i));
    if(!f)continue;
    vector<int>params={k,i,j,A1,B1,C1,D1};
    vector<long long>count=countPartitions(n,partitions,generateConditionsOriginal6_1(params));
    vector<long long> A=Factor(count);
    printPeriodOfSeq(A); 
  }
}
void SearchSp_Original7(int n){
  rep(k,6)rep(i,6)rep(j,6)rep(A1,6)rep(B1,6)rep(C1,6)rep(D1,6)rep(A2,6)rep(B2,6)rep(C2,6)rep(D2,6){
    bool f = (k>=1&&i>=1&&j>=1&&A1>=1&&C1<D1&&D1>=2);
		f=f&&(A2>=1&&C2<D2&&D2>=2);
    if(!f)continue;
    f=f&&(B1>=j*(A1/i));
    f=f&&(B2>=j*(A2/i));
    if(!f)continue;
    vector<int>params={k,i,j,A1,B1,C1,D1,A2,B2,C2,D2};
    vector<long long>count=countPartitions(n,partitions,generateConditionsOriginal7(params));
    vector<long long> A=Factor(count);
    printPeriodOfSeq(A); 
  }
}
void SearchSp_GeneralSchur(int n){
  rep(np,1024)rep(D,11)rep(dist,4)rep(diff,11)rep(residue,1024){
    bool f = (diff>=1 && dist>=1 && D>=1);
		f=f&&(residue<pow(2,diff)&&np<pow(2,D));
    if(!f)continue;
    vector<int>params={np,D,dist,diff,residue};
    vector<long long>count=countPartitions(n,partitions,generateConditionsGeneralSchur(params));
    vector<long long> A=Factor(count);
    printPeriodOfSeq(A); 
  }
}
void SearchSp_GeneralSchur2(int n){
  rep(k,n/4+1){
		if(k==0)continue;
    vector<int>params={k};
    vector<long long>count=countPartitions(n,partitions,generateConditionsGeneralSchur2(params));
    vector<long long> A=Factor(count);
    printPeriodOfSeq(A); 
  }
}
void SearchSp_GeneralGollnitz(int n){
	rep(np,32)rep(dist,6)rep(diff,6)rep(m,6){
		vector<int>params={np,dist,diff,m};
		vector<long long>count=countPartitions(n,partitions,generateConditionsGeneralGollnitz(params));
		vector<long long>A=Factor(count);
		printPeriodOfSeq(A);
	}
}
void SearchSp_Original8(int n){
  rep(np,1024)rep(diff,11)rep(D,11){
		int residue=1;
		int dist=1;
    bool f = (diff>=1  && D>=1);
		f=f&&(residue<pow(2,diff));
    if(!f)continue;
    vector<int>params={np,dist,diff,residue,D};
    vector<long long>count=countPartitions(n,partitions,generateConditionsOriginal8(params));
    vector<long long> A=Factor(count);
    printPeriodOfSeq(A); 
  }
}
void SearchSp_GeneralGollnitz2(int n){
  for(int M=6;M<17;M++)rep(r3,M)rep(r2,r3)rep(r1,r2){
    if(M<=r1+r2 && r1+M<r2+r3)continue;
    vector<int>params={M,r1,r2,r3};
    vector<long long>count=countPartitions(n,partitions,generateConditions_GeneralGollnitz2(params));
    vector<long long> A=Factor(count);
    printPeriodOfSeq(A); 
  }
}

int main(int argc,char *argv[]){
  int n=atoi(argv[1]);
  generatePartition(n,partitions);
	SearchSp_GeneralGollnitz2(n);
}
